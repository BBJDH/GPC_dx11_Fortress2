#include "stdafx.h"
#include "Image_manager.h"



Image_manager::Image_manager()
{
    initialize();
}

void Image_manager::initialize()
{
    Background.Name = "Image/Background/background";
    Background.Length = Vector<2>(BackgroundSIZE_W, BackgroundSIZE_H);
   
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

    iTank.Name = "Image/Tank/Canon_R";
    iTank.Length = Vector<2>(Tank_SIZE, Tank_SIZE);
    //iTank.Location = Vector<2>(Tank_SIZE / 2, Tank_SIZE / 2);
    iMissile.Name = "Image/Bomb/bomb";
    iMissile.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
    //iMissile.Location = Vector<2>(Missile_SIZE / 2, Missile_SIZE / 2);
}

void Image_manager::render_background()
{
    Background.Render();
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


void Image_manager::render_object(Object const& obj, Obj_Type const type)
{
    Engine::Rendering::Image::Component* p_image = nullptr;
    switch (type)
    {
    case Obj_Type::Tank:
    {
        p_image = &iTank;
        break;
    }
    case Obj_Type::Missile:
    {
        p_image = &iMissile;
        break;
    }
    case Obj_Type::Item:
    {
        p_image = &iTank; //미구현
        break;
    }
    default:
        return;
    }
    p_image->Location = { obj.getpos().x-MAPSIZE_W/2,MAPSIZE_H/2-obj.getpos().y };
    p_image->Angle = -obj.getimage_angle()/Radian;
}
void Image_manager::render_tank(std::vector<Tank> const& tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            render_object(tank[i], Image_manager::Obj_Type::Tank);

            if(tank[i].get_state()==Tank::State::Nomal and tank[i].get_side()==Tank::Side::Left)
                iTank.Name = "Image/Tank/Canon_L";

            if(tank[i].get_state()==Tank::State::Nomal and tank[i].get_side()==Tank::Side::Right)
                iTank.Name = "Image/Tank/Canon_R";

            iTank.Render();
        }
    }
}

void Image_manager::render_missile(std::vector<Missile> const& missile)
{
    if (!missile.empty())
    {
        for (size_t i = 0; i < missile.size(); i++)
        {
            render_object(missile[i], Image_manager::Obj_Type::Missile);
            iMissile.Render();

        }
    }
}
