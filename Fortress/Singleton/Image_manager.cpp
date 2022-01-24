#include "stdafx.h"
#include "Image_manager.h"



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


    iTank.Name = "Image/Tank/Canon";
    iTank.Length = Vector<2>(Tank_SIZE, Tank_SIZE);
    iTank.Location = Vector<2>(Tank_SIZE / 2, Tank_SIZE / 2);
    iMissile.Name = "Image/Bomb/bomb";
    iMissile.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
    iMissile.Location = Vector<2>(Missile_SIZE / 2, Missile_SIZE / 2);
}

void Image_manager::render_background()
{
    Background.Render();
}


void Image_manager::render_back_ui(Tank const & tank)
{
    UI_Back.Render();
}

void Image_manager::render_front_ui(Tank const & tank)
{
    UI_Front.Render();
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
    p_image->Render();
}



void Image_manager::render_tank(std::vector<Tank> const& tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            render_object(tank[i], Image_manager::Obj_Type::Tank);
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
        }
    }
}
