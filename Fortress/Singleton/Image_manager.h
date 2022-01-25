#pragma once
#include"SingletonT.h"



class Image_manager : public SingletonT<Image_manager>
{

public:
    enum class Obj_Type
    {
        Tank, Missile, Item
    };

private:

    Engine::Rendering::Image::Component Background;

    Engine::Rendering::Image::UI UI_Back;
    Engine::Rendering::Image::UI UI_Front;
    Engine::Rendering::Image::UI UI_Hp;
    Engine::Rendering::Image::UI UI_Power;
    Engine::Rendering::Image::UI UI_Fuel;

    Engine::Rendering::Image::Component iTank;
    Engine::Rendering::Image::Component iMissile;

    void render_object(Object const& obj, Obj_Type const type);


public:
    Image_manager();
    void initialize();
    void render_background();
    void render_back_ui(Tank const & tank);
    void render_front_ui(Tank const & tank);
    void render_tank(std::vector<Tank> const& tank);
    void render_missile(std::vector<Missile> const& missile);

};
