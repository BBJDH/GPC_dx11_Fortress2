#include "stdafx.h"
#include "Input_manager.h"

Input_manager::Input_manager() :interval{ 0 }
{
}


void Input_manager::debug_right_button()
{
    if (Engine::Input::Get::Key::Press(VK_RBUTTON))
    {
        _Map_manager->make_crater
        (
            {
                _Mouse->x+static_cast<int>(_CAM->pos_win.x),
                _Mouse->y+static_cast<int>(_CAM->pos_win.y)},
            { 50,40 }
        );
    }
}

void Input_manager::debug_left_button(std::vector<Tank*>& tank)
{
    if (Engine::Input::Get::Key::Press(VK_LBUTTON))
    {
        float x = static_cast<float>(_Mouse->x);
        float y = static_cast<float>(_Mouse->y);
        tank.push_back
        (
            new Tank
            (
                {
                    static_cast<int>(_Mouse->x)+_CAM->pos_win.x,
                    static_cast<int>(_Mouse->y)+_CAM->pos_win.y
                },
                Tank_SIZE,
                Tank_SIZE,
                "test",
                "canon",
                Tank::Tank_Type::Canon,
                Color::Red
            )
        );
        tank.back()->ballistics_initialize(0, 0);
    }  
}
void Input_manager::debug_left_button(std::vector<Patterns>& patterns)
{
    if (Engine::Input::Get::Key::Press(VK_LBUTTON))
    {
        patterns.push_back
        (
            Patterns
            (
                "pinwheel",
                {
                    static_cast<int>(_Mouse->x) + _CAM->pos_win.x,
                    static_cast<int>(_Mouse->y) + _CAM->pos_win.y
                }
            )
        );
        patterns.back().ballistics_initialize(0, 0);
    }
}

void Input_manager::key_left(Tank & tank)
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
        find_nextstep(_Map_manager->hmapdc, tank, false);
}

void Input_manager::key_right(Tank & tank)
{
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
        find_nextstep(_Map_manager->hmapdc, tank, true);
}

void Input_manager::key_up(Tank & tank)
{
    if ((GetAsyncKeyState(VK_UP) & 0x8000))
    {
        if(tank.is_myturn() and !tank.is_dead())
            tank.plus_angle(1);
    }
}

void Input_manager::key_down(Tank & tank)
{
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
    {
        if(tank.is_myturn()and !tank.is_dead())
            tank.plus_angle(-1);
    }
}

void Input_manager::key_space(Tank& tank,std::vector<Missile*>& missile)
{
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
        fire(tank,missile,true);
}


void Input_manager::input(std::vector<Tank*>& tank, std::vector<Missile*>& missile, std::vector<Patterns>& patterns, float const deltha)
{
    interval += deltha;
    if (interval > speed)
    {
        interval = 0;
        //debug_left_button(tank);
        //debug_left_button(patterns);
        debug_right_button();
        if (!tank[_Turn->whosturn()]->is_dead()&&!tank[_Turn->whosturn()]->is_falling())
        {
            key_left(*tank[_Turn->whosturn()]);
            key_right(*tank[_Turn->whosturn()]);
            key_up(*tank[_Turn->whosturn()]);
            key_down(*tank[_Turn->whosturn()]);
            key_space(*tank[_Turn->whosturn()],missile);
        }
    }
    if (Engine::Input::Get::Key::Up(VK_SPACE) and !tank[_Turn->whosturn()]->is_dead())
        fire(*tank[_Turn->whosturn()],missile,false);
}

void Input_manager::find_nextstep(HDC const& hmapdc, Tank& tank, bool const isright)
{
    if (tank.is_myturn()and !tank.is_falling())
    {
        _CAM->focus_on();

        unsigned	   stepx = static_cast<unsigned>(tank.getpos().x - 1); //기본 왼쪽일때 시작할 점
        unsigned const stepy = static_cast<unsigned>(tank.getpos().y+tank.getheight()/2 - Tank_Step_H); 
        if (isright)
        {
            stepx = static_cast<unsigned>(tank.getpos().x+1);
            tank.set_side(Tank::Side::Right);
        }
        else
            tank.set_side(Tank::Side::Left);

        //왼쪽/오른쪽 바로앞 위로 3번째 점부터 검사
        //위에 세번째점에서 충돌이면 이동불가
        //이후 아래 두번째점까지 충돌지점을 찾아 옮김
        //충돌지점이 하나도 없다면 오른쪽으로 한칸이동 후 낙하
        for (unsigned i = stepy; i < stepy+Tank_Step_H+2; i++)
        {
            if ( i == stepy or tank.getfuel()==0)
            {
                if (_Physics_manager->Collide(hmapdc, stepx, i))//못올라가면
                {
                    tank.setstate(Tank::State::Stop);

                    return;
                }
            }
            if (_Physics_manager->Collide(hmapdc, stepx, i))//갈수 있으면
            {
                tank.setstate(Tank::State::Move);
                tank.minus_fuel();
                tank.moveto({ static_cast<float>(stepx) ,static_cast<float>(i-tank.getheight()/2)});
                tank.stop_move(_Physics_manager->calc_landing_angle(stepx, i, hmapdc));
                return;
            }
        }
        tank.setstate(Tank::State::Fall); 

        tank.moveto({ static_cast<float>(stepx) ,tank.getpos().y }); //떨어지면
        tank.ballistics_initialize(0,0);
        return;
    }
}
//30도 위에 15도로 사격, 뒤돌면 210도 방향으로부터 -15도이므로 195도
void Input_manager::fire(Tank& tank, std::vector<Missile*>& missile, bool const keyon)
{
    if (tank.is_myturn()and!tank.is_falling())
    {
        if (keyon)
        {
            tank.setstate(Tank::State::Steady);
            tank.plus_power();
        }
        else
        {
            tank.setstate(Tank::State::Fire);
            tank.ani_start();
            //미사일 생성
            //float angle;
            //if (tank.get_side() == Tank::Side::Right)
            //{
            //    angle = -tank.getimage_angle() / Radian 
            //        + tank.getangle_min() + tank.getangle() ;
            //}
            //else
            //{
            //    angle = (-tank.getimage_angle() / Radian +180.0f)
            //        - (tank.getangle_min() + tank.getangle()) ;
            //}
            ////60분법으로 받음
            //double cosval = cos(angle*Radian);
            //double sinval = sin(angle*Radian); 
            //int min_x = static_cast<int>(FIRE_MIN_Length * cosval );
            //int min_y = static_cast<int>(FIRE_MIN_Length * sinval ); 


            _Missile->create_missiles (tank );
            
            tank.setmyturn(false);
        }
    }
}
