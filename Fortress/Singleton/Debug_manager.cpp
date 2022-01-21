#include "stdafx.h"
#include "../stdafx.h"
#include "Debug_manager.h"

void Debug_manager::init_text(Engine::Rendering::Text::Component &text ,
    int const text_location_x,int const text_location_y)
{
    int const width = 150;
    int const height = 20;
    text.Text = ""; //"디버그";// 
    text.Font.Name = "Kostar";
    text.Font.Size = 20;
    text.Font.Bold = false;
    text.Font.Italic = false;
    text.Font.Underlined = false;
    text.Font.StructOut = false;
    text.Color.Red = 255;
    text.Color.Blue = 255;
    text.Color.Green = 255;
    text.Length = { width, height };
    text.Location = { width/2 +width*text_location_x,  height/2 + height*text_location_y  };
}

void Debug_manager::render_text(Engine::Rendering::Text::Component &text, std::string const&str_value)
{
    text.Text = str_value.c_str();//str_p; //"디버그";// 
    text.Render();
}

Debug_manager::Debug_manager()
{
    initialize();
}

void Debug_manager::initialize()
{
    init_text(cursor_window_location_x, 0,0);
    init_text(cursor_window_location_y, 1,0);
    init_text(cursor_window_coodinate_x, 2,0);
    init_text(cursor_window_coodinate_y, 3,0);
    init_text(cursor_cam_location_x, 4,0);
    init_text(cursor_cam_location_y, 5,0);
    init_text(cursor_map_location_x, 6,0);
    init_text(cursor_map_location_y, 7,0);
}

void Debug_manager::rendering()
{
    render_text(cursor_window_location_x,"win_x : "+std::to_string(_Mouse->x));
    render_text(cursor_window_location_y,"win_y : "+std::to_string(_Mouse->y));
    render_text(cursor_window_coodinate_x,"cood_x : "+std::to_string(_Mouse->coordinate_x));
    render_text(cursor_window_coodinate_y,"cood_y : "+std::to_string(_Mouse->coordinate_y));
    render_text(cursor_cam_location_x,"cam_x : "+std::to_string(static_cast<int>(_CAM->pos.x)));
    render_text(cursor_cam_location_y,"cam_y : "+std::to_string(static_cast<int>(_CAM->pos.y)));
    render_text(cursor_map_location_x,"map_x : "+std::to_string(static_cast<int>(_CAM->pos.x) + _Mouse->coordinate_x));
    render_text(cursor_map_location_y,"map_y : "+std::to_string(static_cast<int>(_CAM->pos.y) + _Mouse->coordinate_y));
}

