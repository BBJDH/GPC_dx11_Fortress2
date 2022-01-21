#include "stdafx.h"
#include "Image_manager.h"

void Image_manager::render_object(Object const & obj, Obj_Type const type)
{
    Engine::Rendering::Image::Component * p_image = nullptr;
    switch (type)
    {
    case Obj_Type::Tank:
    {
        p_image = &iTank;
        break;
    }
    case Obj_Type::Missile:
    {
        p_image = &iTank;
        break;
    }
    case Obj_Type::Item:
    {
        p_image = &iTank;
        break;
    }
    default:
        return;
    }
    p_image->Location = {obj.getpos().x,obj.getpos().y};
    p_image->Render();
}

void Image_manager::initialize()
{
    Background.Name = "Image/background";
    Background.Length = Vector<2>(BackgroundSIZE_W, BackgroundSIZE_H) ;
    Map.Name = "Image/Sky_M";
    Map.Length = Vector<2>(MAPSIZE_W, MAPSIZE_H) ;
    UI_Back.Name = "Image/UI_Back";
    UI_Back.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H) ;
    UI_Back.Location = Vector<2>(CAM_SIZE_W/2, CAM_SIZE_H/2); //윈도우 좌표계 좌측상단 0,0 기준
    UI_Front.Name = "Image/UI_Front";
    UI_Front.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H) ;
    UI_Front.Location = Vector<2>(CAM_SIZE_W/2, CAM_SIZE_H/2); //윈도우 좌표계 좌측상단 0,0 기준

    iTank.Name ="Image/Canon";
    iTank.Length = Vector<2>(Tank_SIZE, Tank_SIZE) ;
    iTank.Location = Vector<2>(Tank_SIZE/2, Tank_SIZE/2);
}

void Image_manager::render_background()
{
    Background.Render();
}

void Image_manager::render_map()
{
    Map.Render();
}

void Image_manager::render_back_ui()
{
    UI_Back.Render();
}

void Image_manager::render_front_ui()
{
    UI_Front.Render();
}

void Image_manager::render_tank(std::vector<Tank> const& tank)
{
    if (!tank.empty())
    {
        for (size_t i = 0; i < tank.size(); i++)
        {
            render_object(tank[i],Image_manager::Obj_Type::Tank);
        }
    }
}

void Image_manager::render_missile(std::vector<Missile> const& missile)
{
    if (!missile.empty())
    {
        for (size_t i = 0; i < missile.size(); i++)
        {
            render_object(missile[i],Image_manager::Obj_Type::Missile);
        }
    }
}
