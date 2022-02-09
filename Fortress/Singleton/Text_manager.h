#pragma once
#include"SingletonT.h"


class Text_manager : public SingletonT<Text_manager>
{
public:
    enum class Color
    {
        Green, Red
    };
private:

    float delta=0.0f;
    Engine::Rendering::Text::Component fps;

    //========================  좌표  ==========================//
    //마우스의 윈도우좌표
    Engine::Rendering::Text::Component Ui_angle;
    SIZE const angle_text_size = { 30,15 };
    int const tilt_angle_text_location_x = 125;
    int const launch_angle_text_location_x = 185;
    int const angle_text_location_y = 667;


    void render_tank_angle(Tank const& tank);
public:
    void set_text(Engine::Rendering::Text::Component& text, POINT const& location,
        SIZE const& font_size, std::string const& str_value, Color color);
    void render(std::vector<Tank> const & tank );
    Text_manager();
    void set_delta(float const delta);
    void initialize();
    void rendering();

};