#pragma once
#include"SingletonT.h"
//#include "../Engine/Rendering.h"
class Debug_manager : public SingletonT<Debug_manager>
{
public:

private:

    float delta=0.0f;
    Engine::Rendering::Text::Component fps;

    //========================  좌표  ==========================//
    //마우스의 윈도우좌표
    Engine::Rendering::Text::Component cursor_window_location_x;
    Engine::Rendering::Text::Component cursor_window_location_y;

    //마우스의 윈도우 중점(0,0)기준 xy평면 좌표
    Engine::Rendering::Text::Component cursor_window_coodinate_x;
    Engine::Rendering::Text::Component cursor_window_coodinate_y;

    //카메라 가운데 초점의 xy평면 좌표
    Engine::Rendering::Text::Component cursor_cam_location_x;
    Engine::Rendering::Text::Component cursor_cam_location_y;
    
    //카메라 좌측상단끝점의 hdc 좌표
    Engine::Rendering::Text::Component cursor_cam_win_x;
    Engine::Rendering::Text::Component cursor_cam_win_y;

    //마우스의 dx world 좌표
    Engine::Rendering::Text::Component cursor_map_location_x;
    Engine::Rendering::Text::Component cursor_map_location_y;


    //========================  탱크  ==========================//

    Engine::Rendering::Text::Component tank_state;



    void init_text(Engine::Rendering::Text::Component &text ,
        int const text_location_x,int const text_location_y);
    void render_text(Engine::Rendering::Text::Component &text, std::string const&str_value);

public:
    void set_delta(float const delta);
    Debug_manager();
    void initialize();
    void rendering();

};