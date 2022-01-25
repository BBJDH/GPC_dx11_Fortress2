#pragma once
#include"SingletonT.h"
//#include "../Engine/Rendering.h"
class Debug_manager : public SingletonT<Debug_manager>
{
public:

private:

    float delta=0.0f;
    Engine::Rendering::Text::Component fps;

    Engine::Rendering::Text::Component cursor_window_location_x;
    Engine::Rendering::Text::Component cursor_window_location_y;
    Engine::Rendering::Text::Component cursor_window_coodinate_x;
    Engine::Rendering::Text::Component cursor_window_coodinate_y;
    Engine::Rendering::Text::Component cursor_cam_location_x;
    Engine::Rendering::Text::Component cursor_cam_location_y;
    Engine::Rendering::Text::Component cursor_cam_win_x;
    Engine::Rendering::Text::Component cursor_cam_win_y;
    Engine::Rendering::Text::Component cursor_map_location_x;
    Engine::Rendering::Text::Component cursor_map_location_y;

    void init_text(Engine::Rendering::Text::Component &text ,
        int const text_location_x,int const text_location_y);
    void render_text(Engine::Rendering::Text::Component &text, std::string const&str_value);

public:
    void set_delta(float const delta);
    Debug_manager();
    void initialize();
    void rendering();

};