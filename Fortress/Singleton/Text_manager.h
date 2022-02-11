#pragma once
#include"SingletonT.h"


class Text_manager : public SingletonT<Text_manager>
{
public:
    enum class Color
    {
        Green, Red
    };
    enum class Font
    {
        Damage, Red
    };
private:

    float delta=0.0f;
    Engine::Rendering::Text::Component fps;

    //========================  좌표  ==========================//
    //마우스의 윈도우좌표
    Engine::Rendering::Text::Component Ui_angle;
    Engine::Rendering::Text::Component text;
    Engine::Rendering::Image::Component text_img;

    SIZE const angle_text_size = { 30,15 };
    int const tilt_angle_text_location_x = 125;
    int const launch_angle_text_location_x = 185;
    int const angle_text_location_y = 667;
    //void render_tank_text(Tank const & tank);
    void render_single_text(POINT const& location, SIZE const& font_size,
        char const & value, Font font);
public:
    Text_manager();
    void set_text(Engine::Rendering::Text::Component& text, POINT const& location,
        SIZE const& font_size, std::string const& str_value, Color color);
    void render_tank_angle(Tank const& tank);
    void render_text(POINT const& location, int const& font_size,
        std::string const& str_value, Font font);
    void render_damage(Tank const & tank );
    void render_tank_name(Tank const& tank);
    void render(std::vector<Tank>& tank);

};

//문자열을 받아서 문자 한개씩 지정된 위치로부터 크기만큼 띄워가면서 출력
//문자열을 받아서 한자한자를 판독해서 문자 이미지로 치환하는 함수를 작성
//띄어쓰기 인식기능도 있어야함
//