#include "stdafx.h"
#include "Image_manager.h"



Image_manager::Image_manager()
{

}

void Image_manager::set_image(Engine::Rendering::Image::Component & image, _float2 const& position, _float2 const& length, float angle)
{
    image.Location = { position.x, position .y};
    image.Length = { length.x,length.y };
    image.Angle = angle;
}

void Image_manager::set_image(Engine::Rendering::Image::UI & image, _float2 const& position, _float2 const& length, float angle)
{
    image.Location = { position.x, position.y };
    image.Length = { length.x,length.y };
    image.Angle = angle;
}

void Image_manager::render_loading()
{
    world_image.Name = "Image/Screen/loading";
    set_image(world_image, { 0,0 }, { CAM_SIZE_W, CAM_SIZE_H });
    world_image.Render();
}

void Image_manager::render_background(_float2 const& position, _float2 const& length)
{
    set_background(position, length);
    world_image.Render();
}


void Image_manager::render_back_ui(Tank const & tank)
{
    render_back_pannel();

    int  img_angle = -static_cast<int>(tank.getimage_angle()/Radian); //탱크 입장에서 지평선 기준으로 바라보는 각도
    int  support_angle = img_angle;             //계산에 반영할 각도, 오른쪽을 본다면 0도 왼쪽을 본다면 180도
    int  barrel_angle = tank.getangle();
    int  min_angle = tank.getangle_min();
    int  max_angle = tank.getangle_max();
    int  white_line_addtional_length = 0;
    if (tank.get_side() == Tank::Side::Left)
    {
        support_angle += 180;
        barrel_angle *= -1;
        min_angle *= -1;
        max_angle *= -1;
    }
    //탱크 포신이 움직일 수 있는 최소각 최대각 현재 포신의 각도
    ui_angle_line(UI_ANGLE_Length, support_angle + min_angle, 1, Color::Yellow);
    ui_angle_line(UI_ANGLE_Length, support_angle + max_angle, 1, Color::Yellow);
    ui_angle_line(UI_ANGLE_Length, support_angle + min_angle + barrel_angle, 1, Color::Red);

    if (abs(img_angle) <= 40) //40도 이하는 흰선 길이가 짧아보여서 보정
        white_line_addtional_length = 10;
    else
        white_line_addtional_length = 5;
    //탱크가 서있는 지표면의 각도
    ui_angle_line(UI_ANGLE_Length+white_line_addtional_length, img_angle, 2,  Color::White);
    ui_angle_line(UI_ANGLE_Length+white_line_addtional_length, img_angle+180, 2,  Color::White);
}

void Image_manager::render_front_ui(Tank const & tank)
{
    render_front_pannel();

    render_pannel_hp(tank.gethp());

    render_pannel_power(tank.getpower());

    render_pannel_fuel(tank);
}

void Image_manager::render_tanks_hp(std::vector<Tank> const& tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            render_tank_hp(tank[i]);
        }
    }
}

void Image_manager::render_ui(std::vector<Tank> const& tank)
{
    render_tanks_hp(tank);
    render_back_ui(tank[_Turn->whosturn()]);
    render_front_ui(tank[_Turn->whosturn()]);
    _Text_manager->render_tank_angle(tank[_Turn->whosturn()]);
}

void Image_manager::render_gameover()
{
    view_image.Name = "Image/Screen/gameover";
    set_image(view_image, { CAM_SIZE_W / 2, CAM_SIZE_H / 2 }, { CAM_SIZE_W, CAM_SIZE_H });
    view_image.Render();
}


void Image_manager::render_main_text(_float2 test_location, _float2 test_length)
{
    view_image.Name = "Image/Text/start_text2";
    set_image(view_image, test_location, test_length );
    view_image.Render();
}

void Image_manager::render_main(_float2 test_location, _float2 test_length)
{
    view_image.Name = "Image/Screen/start";
    set_image(view_image,  test_location, test_length);
    view_image.Render();
}

void Image_manager::render_lobby_back()
{
    view_image.Name = "Image/Screen/lobby";
    set_image
    (
        view_image,
        { CAM_SIZE_W / 2, CAM_SIZE_H / 2 },
        { CAM_SIZE_W, CAM_SIZE_H }
    );
    view_image.Render();

}

void Image_manager::render_tank_image(std::string const& name, _float2 const& position, _float2 const& length)
{
    if (name.empty())
        return;

    std::string const location = "Image/Tank/" + name;
    view_image.Name = location.c_str();
    set_image(view_image, position, length);
    view_image.Render();
}

void Image_manager::render_color(Color color, _float2 const& position, _float2 const& length)
{

    assert(color >= Color::Red and color <= Color::Pink);

    std::string const location = "Image/Color/" + str_color[static_cast<int>(color)];
    view_image.Name = location.c_str();
    set_image(view_image, position, length);
    view_image.Render();
}

void Image_manager::render_selected_slot(_float2 const& position, _float2 const& length)
{
    view_image.Name = "Image/Button/Lobby/selected_slot";
    set_image(view_image, position, length);
    view_image.Render();
}

void Image_manager::set_background(_float2 const& position ,_float2 const& length)
{
    world_image.Name = "Image/Background/background";
    set_image(world_image, position, length);

}

void Image_manager::set_minimap_background()
{
    float const minimap_height = static_cast<float>(MINIMAP_SIZE_H + _Map_manager->MINI_UI_SIZE);
    world_image.Name = "Image/Background/background_alpha";
    set_image
    (
        world_image,
        { 
            static_cast<float>(_Map_manager->minimap_loc.x + MINIMAP_SIZE_W / 2),
            static_cast<float>(_Map_manager->minimap_loc.y - minimap_height / 2)
        },
        { MINIMAP_SIZE_W,minimap_height }
    );

}

void Image_manager::render_back_pannel()
{
    view_image.Name = "Image/UI/UI_Back";
    set_image(view_image, { CAM_SIZE_W / 2, CAM_SIZE_H / 2 }, { CAM_SIZE_W, CAM_SIZE_H });
    view_image.Render();
}

void Image_manager::render_front_pannel()
{
    view_image.Name = "Image/UI/UI_Front";
    set_image(view_image, { CAM_SIZE_W / 2, CAM_SIZE_H / 2 }, { CAM_SIZE_W, CAM_SIZE_H });
    view_image.Render();
}

void Image_manager::render_pannel_hp(int const hp)
{
    if (hp < 400)
        view_image.Name = "Image/UI/Red";
    else
        view_image.Name = "Image/UI/Green";
    set_image
    (
        view_image,
        {
            static_cast<float>(UI_Bar_X + hp * UI_HP_MUL / 2),
            UI_HP_Y
        },
        {
            static_cast<float>(hp * UI_HP_MUL),
            UI_Bar_H
        }
    );
    view_image.Render();
}

void Image_manager::render_pannel_power(int const power)
{
    view_image.Name = "Image/UI/Red";
    set_image
    (
        view_image,
        {
            static_cast<float>(UI_Bar_X + power * UI_POWER_MUL / 2),
            UI_POWER_Y
        },
        {
            static_cast<float>(power * UI_POWER_MUL),
            UI_Bar_H
        }
    );
    view_image.Render();
}

void Image_manager::render_pannel_fuel(Tank const & tank)
{
    view_image.Name = "Image/UI/Yellow";
    float const fuel_mul = static_cast<float>((UI_Fuel_MUL / tank.get_maxfuel()) * 100);
    float const fuel = static_cast<float const>(tank.getfuel());
    set_image
    (
        view_image,
        {
            static_cast<float>(UI_Bar_X + fuel * fuel_mul / 2),
            UI_FUEL_Y
        },
        {
            static_cast<float>(fuel * fuel_mul),
            UI_Bar_H
        }
    );

    view_image.Render();
}

void Image_manager::render_line(POINT const& location, unsigned const length,
    unsigned const thickness, float const angle, Color color)
{
    switch (color)
    {
    case Color::Red:
    {
        view_image.Name = "Image/UI/angle_r";
        break;
    }
    case Color::Yellow:
    {
        view_image.Name = "Image/UI/angle_y";
        break;
    }
    case Color::White:
    {
        view_image.Name = "Image/UI/angle_w";
        break;
    }
    default:
        break;
    }
    set_image
    (
        view_image,
        { 
            static_cast<float>(location.x),
            static_cast<float>(location.y)
        },
        { 
            static_cast<float>(length   ),
            static_cast<float>(thickness)
        },
        angle
    );

    view_image.Render();
}

void Image_manager::ui_angle_line(int const length, int const angle, int const thickness, Color color)
{
    //중점으로부터 선의 반길이만큼 떨어진곳에 각도만큼 회전된 출력위치를 구하고 그곳에
    // 선을 각도만큼 기울여서 출력, 선이 각도만큼 회전하는것처럼 보이게 함
    //임의의 점으로부터 length 만큼 떨어진곳에 이미지를출력
    double cosval = cos(-angle*Radian); //윈도우 좌표계 기준이므로  각도를 거꾸로
    double sinval = sin(-angle*Radian); 
    int max_x = static_cast<int>(length * cosval );
    int max_y = static_cast<int>(length * sinval ); 

    render_line //이미지 출력(각도를 나타내는 선)
    (//UI_ANGLE_CENTER_X,UI_ANGLE_CENTER_Y 는 각도UI의 중점 위치 필요하면 이동가능
        { UI_ANGLE_CENTER_X + max_x,UI_ANGLE_CENTER_Y + max_y },
        length*2,//length는 선 길이의 반
        thickness,
        static_cast<float>(angle),//선을 그려서 각도만큼 기울여서 출력
        color
    );

}

void Image_manager::render_tank_hp_base(_float2 const& position)
{

    world_image.Name = "Image/UI/base_bar";
    set_image
    (
        world_image,
        {
            position.x - MAPSIZE_W / 2,
            MAPSIZE_H / 2 - position.y - Tank_HP_Bar_Location_H
        },
        {
            Tank_HP_Bar_W,
            Tank_HP_Bar_H
        }
        );
    world_image.Render();
}

void Image_manager::render_tank_hp_bar(_float2 const& position, int const hp)
{
   
    if (hp < TANK_DANGER_HP)
        world_image.Name = "Image/UI/red_bar";
    else if (hp < 700)
        world_image.Name = "Image/UI/orange_bar";
    else
        world_image.Name = "Image/UI/blue_bar";
    set_image
    (
        world_image,
        { 
            static_cast<float>(position.x + hp * Tank_HP_Bar_Mul / 2 - MAPSIZE_W / 2 - Tank_HP_Bar_Location_W) ,
            static_cast<float>(MAPSIZE_H / 2 - position.y - Tank_HP_Bar_Location_H)
        },
        { 
            static_cast<float>(hp * Tank_HP_Bar_Mul),
            Tank_HP_Bar_H
        }
    );
    this->world_image.Render();
}

void Image_manager::render_tank_hp(Tank const& tank)
{
    if (tank.gethp() == 0)
        return;
    render_tank_hp_base(tank.getpos());
    render_tank_hp_bar(tank.getpos(), tank.gethp());
}

void Image_manager::render_minimap_background()
{
    set_minimap_background();
    world_image.Render();
}

void Image_manager::render_minimap_object(Object const& obj, bool is_turn)
{
    float const correct = obj.getpos().y / MAPSIZE_H; // 미니맵 y좌표 보정값

    if (is_turn)
        view_image.Name = "Image/UI/Green";
    else
        view_image.Name = "Image/UI/Red";

    set_image
    (
        view_image,
        {
            static_cast<float>(_Map_manager->minimap_loc.x + obj.getpos().x / 10),
            static_cast<float>(_Map_manager->minimap_loc.y + obj.getpos().y / 10 + (_Map_manager->MINI_UI_SIZE) * correct)
        },
        { 5,5 },
        obj.getimage_angle() / Radian
    );

    view_image.Render();
    return ;
}


void Image_manager::render_minimap_tank(std::vector<Tank> const& tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            if(i != _Turn->whosturn() and tank[i].get_state() != Tank::State::Dead)
                render_minimap_object(tank[i],false);

        }
        if(tank[_Turn->whosturn()].get_state() != Tank::State::Dead)
            render_minimap_object(tank[_Turn->whosturn()], true);
    }
}

void Image_manager::render_minimap_cambox()
{
    LONG const cam_minimap_location_x = static_cast<LONG>(_CAM->pos_win.x/10.0f);
    LONG const cam_minimap_location_y = static_cast<LONG>(_CAM->pos_win.y/10.0f);
    LONG const mini_cam_size_w = CAM_SIZE_W / 10;
    LONG const mini_cam_size_h = CAM_SIZE_H / 10;

    render_line
    (
        {
            _Map_manager->minimap_loc.x + cam_minimap_location_x ,
            _Map_manager->minimap_loc.y + cam_minimap_location_y + mini_cam_size_h / 2
        },
        mini_cam_size_h,
        1,
        90,
        Color::White
    );
    render_line
    (
        {
            _Map_manager->minimap_loc.x + cam_minimap_location_x + mini_cam_size_w,
            _Map_manager->minimap_loc.y + cam_minimap_location_y + mini_cam_size_h / 2
        },
        mini_cam_size_h,
        1,
        90,
        Color::White
    );
    render_line
    (
        { 
            _Map_manager->minimap_loc.x+ cam_minimap_location_x + mini_cam_size_w /2,
            _Map_manager->minimap_loc.y+ cam_minimap_location_y
        },
        mini_cam_size_w,
        1,
        0,
        Color::White
    );
    render_line
    (
        { 
            _Map_manager->minimap_loc.x + cam_minimap_location_x + mini_cam_size_w / 2,
            _Map_manager->minimap_loc.y + cam_minimap_location_y+ mini_cam_size_h
        },
        mini_cam_size_w,
        1,
        0,
        Color::White
    );
}

