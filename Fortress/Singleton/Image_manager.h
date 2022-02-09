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
        Red, Yellow,White
    };

private:

    Engine::Rendering::Image::Component Background;
    Engine::Rendering::Image::Component Loading;

    Engine::Rendering::Image::UI UI_Back;
    Engine::Rendering::Image::UI UI_Front;
    Engine::Rendering::Image::UI UI_Hp;
    Engine::Rendering::Image::UI UI_Power;
    Engine::Rendering::Image::UI UI_Fuel;
    Engine::Rendering::Image::UI UI_Line;


    Engine::Rendering::Image::Component Tank_Hp;
    Engine::Rendering::Image::Component Tank_Hp_Bar;

    Engine::Rendering::Image::UI Red;
    Engine::Rendering::Image::UI Green;
    void set_background();
    void set_minimap_background();
    void render_line(POINT const & location,size_t const length,
        size_t const thickness, float const angle, Color color);
    void ui_angle_line(int const length, int const angle,
        int const thickness, Color color);
    void render_tank_hp(Tank const & tank);

    void render_minimap_object(Object const& obj, bool is_turn);
    
    //game over
private:
    Engine::Rendering::Image::UI Gameover;


public:
    Image_manager();
    void initialize();
    void render_background();
    void render_loading();
    void render_minimap_background();
    void render_back_ui(Tank const & tank);
    void render_front_ui(Tank const & tank);
    void render_tanks_hp(std::vector<Tank> const& tank);
    void render_ui(std::vector<Tank> const& tank);
    
    void render_minimap_tank(std::vector<Tank> const& tank);
    void render_minimap_cambox();

    void render_gameover();

    //애니메이션구현이후로 미사용, 테스트용
    //void render_missile(std::vector<Missile> const& missile);

};
