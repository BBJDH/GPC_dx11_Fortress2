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
    Engine::Rendering::Text::Component text;
    Engine::Rendering::Image::Component text_img;

    //���� UI ��� ����
    SIZE const angle_text_size = { 30,15 };
    int const tilt_angle_text_location_x = 125;
    int const launch_angle_text_location_x = 185;
    int const angle_text_location_y = 667;

    //fps UI ��� ����
    int const fps_loc_x = 50;
    int const fps_loc_y = 15;
    int const fps_width = 80;
    int const fps_heght = 25;

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
    void render_fps();
    void render(std::vector<Tank>& tank);

};

//���ڿ��� �޾Ƽ� ���� �Ѱ��� ������ ��ġ�κ��� ũ�⸸ŭ ������鼭 ���
//���ڿ��� �޾Ƽ� �������ڸ� �ǵ��ؼ� ���� �̹����� ġȯ�ϴ� �Լ��� �ۼ�
//���� �νı�ɵ� �־����
//