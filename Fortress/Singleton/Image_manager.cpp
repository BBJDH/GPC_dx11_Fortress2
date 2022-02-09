#include "stdafx.h"
#include "Image_manager.h"



Image_manager::Image_manager()
{
    initialize();
}

void Image_manager::initialize()
{
    set_background();
   
    Loading.Name = "Image/Screen/loading";
    Loading.Location = { 0,0 };
    Loading.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);

    UI_Back.Name = "Image/UI/UI_Back";
    UI_Back.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    UI_Back.Location = Vector<2>(CAM_SIZE_W / 2, CAM_SIZE_H / 2); //윈도우 좌표계 좌측상단 0,0 기준
    UI_Front.Name = "Image/UI/UI_Front";
    UI_Front.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    UI_Front.Location = Vector<2>(CAM_SIZE_W / 2, CAM_SIZE_H / 2); //윈도우 좌표계 좌측상단 0,0 기준

    UI_Hp.Name = "Image/UI/Green";
    UI_Power.Name = "Image/UI/Red";
    UI_Fuel.Name = "Image/UI/Yellow";
    UI_angle.Name ="Image/UI/angle_r";

    Tank_Hp.Name ="Image/UI/blue_bar";
    Tank_Hp_Bar.Name ="Image/UI/base_bar";

    Red.Name = "Image/UI/Red";
    Red.Length = Vector<2>(5, 5);
    Green.Name = "Image/UI/Green";
    Green.Length = Vector<2>(5, 5);

    Gameover.Name = "Image/Screen/gameover";
    Gameover.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    Gameover.Location = Vector<2>(CAM_SIZE_W / 2, CAM_SIZE_H / 2); //윈도우 좌표계 좌측상단 0,0 기준

}

void Image_manager::render_background()
{
    Background.Render();
}

void Image_manager::render_loading()
{
    Loading.Render();
}


void Image_manager::render_back_ui(Tank const & tank)
{
    UI_Back.Render();
    int  img_angle = -static_cast<int>(tank.getimage_angle()/Radian);
    int  fire_angle = tank.getangle();
    int  min_angle = tank.getangle_min();
    int  max_angle = tank.getangle_max();
    if (tank.get_side() == Tank::Side::Left)
    {
        img_angle += 180;
        fire_angle *= -1;
        min_angle *= -1;
        max_angle *= -1;
    }

    ui_angle_line(img_angle + min_angle, Color::Yellow,UI_ANGLE_Length);
    ui_angle_line(img_angle + max_angle, Color::Yellow,UI_ANGLE_Length);
    ui_angle_line(img_angle + min_angle + fire_angle ,Color::Red,UI_ANGLE_Length);

    UI_angle.Render();
}

void Image_manager::render_front_ui(Tank const & tank)
{
    UI_Front.Render();

    if(tank.gethp()<400)
        UI_Hp.Name = "Image/UI/Red";
    else
        UI_Hp.Name = "Image/UI/Green";


    UI_Hp.Location = {UI_Bar_X + tank.gethp()*UI_HP_MUL/2,UI_HP_Y};
    UI_Hp.Length = {tank.gethp()*UI_HP_MUL,UI_Bar_H};

    UI_Power.Location = {UI_Bar_X + tank.getpower() * UI_POWER_MUL/2 , UI_POWER_Y};
    UI_Power.Length = {tank.getpower() * UI_POWER_MUL , UI_Bar_H};

    UI_Fuel.Location = {UI_Bar_X + tank.getfuel()*UI_Fuel_MUL/2 , UI_FUEL_Y};
    UI_Fuel.Length = {tank.getfuel()*UI_Fuel_MUL , UI_Bar_H};
    UI_Hp.Render();
    UI_Power.Render();
    UI_Fuel.Render();

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
}

void Image_manager::render_gameover()
{
    Gameover.Render();
}


void Image_manager::set_background()
{
    Background.Name = "Image/Background/background";

    Background.Location = {0,0};
    Background.Length = Vector<2>(BackgroundSIZE_W, BackgroundSIZE_H);
}

void Image_manager::set_minimap_background()
{
    Background.Name = "Image/Background/background_alpha";
    //Background.Name = "Image/Background/start";

    Background.Location = {_Map_manager->minimap_loc.x+MINIMAP_SIZE_W/2,_Map_manager->minimap_loc.y-MINIMAP_SIZE_H/2};
    Background.Length = {MINIMAP_SIZE_W,MINIMAP_SIZE_H};
}

void Image_manager::ui_angle_line(int const angle, Color color, int const length)
{
    switch (color)
    {
    case Image_manager::Color::Red:
    {
        UI_angle.Name ="Image/UI/angle_r";
        break;
    }
    case Image_manager::Color::Yellow:
    {
        UI_angle.Name ="Image/UI/angle_y";
        break;
    }
    default:
        break;
    }

    double cosval = cos(-angle*Radian);
    double sinval = sin(-angle*Radian);
    int max_x = static_cast<int>(length * cosval );
    int max_y = static_cast<int>(length * sinval ); 


    UI_angle.Location = {UI_ANGLE_CENTER_X+max_x,UI_ANGLE_CENTER_Y+max_y};
    UI_angle.Length = {length*2,1};
    UI_angle.Angle = static_cast<float>(angle);
    UI_angle.Render();
}

void Image_manager::render_tank_hp(Tank const& tank)
{
    this->Tank_Hp_Bar.Length = Vector<2>(Tank_HP_Bar_W, Tank_HP_Bar_H);
    this->Tank_Hp_Bar.Location = { tank.getpos().x - MAPSIZE_W / 2,MAPSIZE_H / 2 - tank.getpos().y-Tank_HP_Bar_Location_H };
    if (tank.gethp() == 0)
        return;

    this->Tank_Hp_Bar.Render();

    unsigned const hp = tank.gethp();
    if(hp<TANK_DANGER_HP)
        Tank_Hp.Name = "Image/UI/red_bar";
    else if(hp<700)
        Tank_Hp.Name = "Image/UI/orange_bar";
    else
        Tank_Hp.Name = "Image/UI/blue_bar";
    this->Tank_Hp.Length =  Vector<2>(hp*Tank_HP_Bar_Mul, Tank_HP_Bar_H);
    this->Tank_Hp.Location = { tank.getpos().x+hp*Tank_HP_Bar_Mul/2 - MAPSIZE_W / 2-Tank_HP_Bar_Location_W ,MAPSIZE_H / 2 - tank.getpos().y-Tank_HP_Bar_Location_H };
    this->Tank_Hp.Render();


}

void Image_manager::render_minimap_background()
{
    set_minimap_background();
    render_background();
    set_background();
}

void Image_manager::render_minimap_object(Object const& obj, bool is_turn)
{
    if (is_turn)
    {
        Green.Location = { _Map_manager->minimap_loc.x+obj.getpos().x/10, _Map_manager->minimap_loc.y+obj.getpos().y/10 };
        Green.Angle = -obj.getimage_angle()/Radian;
        Green.Render();
        return;
    }
    Red.Location = {_Map_manager->minimap_loc.x+ obj.getpos().x/10, _Map_manager->minimap_loc.y+obj.getpos().y/10 };
    Red.Angle = -obj.getimage_angle()/Radian;
    Red.Render();
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




//void Image_manager::render_missile(std::vector<Missile> const& missile)
//{
//    if (!missile.empty())
//    {
//        for (size_t i = 0; i < missile.size(); i++)
//        {
//            render_object(missile[i], Image_manager::Obj_Type::Missile);
//            iMissile.Render();
//
//        }
//    }
//}
