#pragma once
#include"SingletonT.h"
//#include "../Engine/Rendering.h"
class Debug_manager : public SingletonT<Debug_manager>
{
public:

private:

    float delta=0.0f;
    Engine::Rendering::Text::Component fps;

    //========================  ��ǥ  ==========================//
    //���콺�� ��������ǥ
    Engine::Rendering::Text::Component cursor_window_location_x;
    Engine::Rendering::Text::Component cursor_window_location_y;

    //���콺�� ������ ����(0,0)���� xy��� ��ǥ
    Engine::Rendering::Text::Component cursor_window_coodinate_x;
    Engine::Rendering::Text::Component cursor_window_coodinate_y;

    //ī�޶� ��� ������ xy��� ��ǥ
    Engine::Rendering::Text::Component cursor_cam_location_x;
    Engine::Rendering::Text::Component cursor_cam_location_y;
    
    //ī�޶� ������ܳ����� hdc ��ǥ
    Engine::Rendering::Text::Component cursor_cam_win_x;
    Engine::Rendering::Text::Component cursor_cam_win_y;

    //���콺�� dx world ��ǥ
    Engine::Rendering::Text::Component cursor_map_location_x;
    Engine::Rendering::Text::Component cursor_map_location_y;


    //========================  ��ũ  ==========================//

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