#pragma once
#include"SingletonT.h"



class Image_manager : public SingletonT<Image_manager>
{

public:
    enum class Obj_Type
    {
        Tank, Missile, Item
    };
    enum class Color
    {
        Red, Yellow
    };

private:

    Engine::Rendering::Image::Component Background;

    Engine::Rendering::Image::UI UI_Back;
    Engine::Rendering::Image::UI UI_Front;
    Engine::Rendering::Image::UI UI_Hp;
    Engine::Rendering::Image::UI UI_Power;
    Engine::Rendering::Image::UI UI_Fuel;
    Engine::Rendering::Image::UI UI_angle;

    Engine::Rendering::Image::UI Tank_Hp;
    Engine::Rendering::Image::UI Tank_Hp_Bar;

    Engine::Rendering::Image::Component iTank;
    Engine::Rendering::Image::Component iMissile;

    void render_object(Object const& obj, Obj_Type const type);
    void ui_angle_line( int const angle,Color color);

public:
    Image_manager();
    void initialize();
    void render_background();
    void render_back_ui(Tank const & tank);
    void render_front_ui(Tank const & tank);
    void render_tank(std::vector<Tank> const& tank);
    void render_missile(std::vector<Missile> const& missile);

};
