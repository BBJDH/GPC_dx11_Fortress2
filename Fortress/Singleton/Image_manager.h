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
    Engine::Rendering::Image::Component Map;
    Engine::Rendering::Image::UI UI_Back;
    Engine::Rendering::Image::UI UI_Front;

    Engine::Rendering::Image::Component iTank;
    Engine::Rendering::Image::Component iMissile;

    void render_object(Object const& obj, Obj_Type const type);


public:
    void initialize();
    void render_background();
    void render_back_ui();
    void render_front_ui();
    void render_tank(std::vector<Tank> const& tank);
    void render_missile(std::vector<Missile> const& missile);

};
