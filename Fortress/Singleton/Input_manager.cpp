#include "stdafx.h"
#include "Input_manager.h"



void Input_manager::input(std::vector<Tank>& tank, std::vector<Missile>& missile, float const deltha)
{
    interval += deltha;
    if (interval > speed)
    {
        interval = 0;
        //if (Engine::Input::Get::Key::Press(VK_LBUTTON))
        //{
        //    float x = static_cast<float>(_Mouse->x);
        //    float y = static_cast<float>(_Mouse->y);
        //    tank.push_back
        //    (
        //        Tank
        //        (
        //            {
        //                static_cast<int>(_Mouse->x)+_CAM->pos_win.x,
        //                static_cast<int>(_Mouse->y)+_CAM->pos_win.y
        //            },
        //            Tank_SIZE,
        //            Tank_SIZE
        //        )
        //    );
        //    tank.back().ballistics_initialize(0, 0);
        //}   
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
        if (!tank[_Turn->whosturn()].is_dead())
        {
            if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
                find_nextstep(_Map_manager->hmapdc, tank[_Turn->whosturn()], false);
            if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
                find_nextstep(_Map_manager->hmapdc, tank[_Turn->whosturn()], true);
            if ((GetAsyncKeyState(VK_UP) & 0x8000))
            {
                if(tank[_Turn->whosturn()].is_myturn() and !tank[_Turn->whosturn()].is_dead())
                    tank[_Turn->whosturn()].plus_angle(1);
            }
            if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
            {
                if(tank[_Turn->whosturn()].is_myturn()and !tank[_Turn->whosturn()].is_dead())
                    tank[_Turn->whosturn()].plus_angle(-1);
            }
            if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
                fire(tank[_Turn->whosturn()],missile,true);

        }

    }
    if (Engine::Input::Get::Key::Up(VK_SPACE) and !tank[_Turn->whosturn()].is_dead())
        fire(tank[_Turn->whosturn()],missile,false);
}

void Input_manager::find_nextstep(HDC const& hmapdc, Tank& tank, bool const isright)
{
    if (tank.is_myturn()and !tank.is_falling())
    {
        unsigned	   stepx = static_cast<unsigned>(tank.getpos().x - 1); //기본 왼쪽일때 시작할 점
        unsigned const stepy = static_cast<unsigned>(tank.getpos().y+tank.getheight()/2 - 3); 
        if (isright)
            stepx = static_cast<unsigned>(tank.getpos().x+1);

        //왼쪽/오른쪽 바로앞 위로 3번째 점부터 검사
        //위에 세번째점에서 충돌이면 이동불가
        //이후 아래 두번째점까지 충돌지점을 찾아 옮김
        //충돌지점이 하나도 없다면 오른쪽으로 한칸이동 후 낙하
        for (unsigned i = stepy; i < stepy+7; i++)
        {
            if ( i == stepy)
            {
                if (_Physics_manager->Collide(hmapdc, stepx, i))
                {
                    tank.setstate(Tank::State::Stop_right);
                    return;
                }
            }
            if (_Physics_manager->Collide(hmapdc, stepx, i))
            {
                tank.moveto({ static_cast<float>(stepx) ,static_cast<float>(i-tank.getheight()/2)});
                tank.stop_move(_Physics_manager->calc_landing_angle(stepx, i, hmapdc));
                return;
            }
        }
        tank.moveto({ static_cast<float>(stepx) ,tank.getpos().y });
        tank.ballistics_initialize(0,0);
        return;
    }
}

void Input_manager::fire(Tank& tank, std::vector<Missile>& missile, bool const keyon)
{
    if (tank.is_myturn()and!tank.is_falling())
    {
        if (keyon)
            tank.plus_power();
        else
        {
            //미사일 생성
            float const angle = -tank.getimage_angle() / Radian + tank.getangle_min() + tank.getangle();
            //60분법으로 받음
            double cosval = cos(angle*Radian);
            double sinval = sin(angle*Radian); 
            int min_x = static_cast<int>(FIRE_MIN_Length * cosval );
            int min_y = static_cast<int>(FIRE_MIN_Length * sinval ); 

            missile.push_back(Missile({ tank.getpos().x+min_x,tank.getpos().y -min_y}, 31, 33));
            missile.back().ballistics_initialize(
                angle,
                static_cast<float const>(tank.getpower() * FIRE_MUL));
            tank.setmyturn(false);
            missile.back().setmyturn(true);
        }
    }
}
