#pragma once
#include"SingletonT.h"



class Image_manager : public SingletonT<Image_manager>
{

public:

    enum class Color  //라인 색상
    {
        Red, Yellow,White
    };

private:
    Engine::Rendering::Image::Component world_image;
    Engine::Rendering::Image::UI view_image;


private:
    //선을 그리는 함수
    void render_line(POINT const& location, unsigned const length,
        unsigned const thickness, float const angle, Color color);
    
    //  ==================== Lobby ==================

    //  ==================== Battle ==================
    //map render
    void set_background();

    //minimap render
    void set_minimap_background();
    void render_minimap_object(Object const& obj, bool is_turn);
    void render_minimap_enemy(_float2 const& position, float const angle);
    void render_minimap_ally(_float2 const& position, float const angle);

    //ui pannel
    void render_back_pannel();
    void render_front_pannel();

    //ui pannel bar
    void render_pannel_hp(int const hp);
    void render_pannel_power(int const power);
    void render_pannel_fuel(int const fuel);

    //ui pannel angle line
    void ui_angle_line(int const length, int const angle,
        int const thickness, Color color);

    //UI render 함수 집합
    void render_back_ui(Tank const& tank);
    void render_front_ui(Tank const& tank);


    //tank world hp bar
    void render_tank_hp_base(_float2 const & position);
    void render_tank_hp_bar(_float2 const & position, int const hp);
    void render_tank_hp(Tank const & tank);
    void render_tanks_hp(std::vector<Tank> const& tank);

    
    //game over


public:
    Image_manager();
    void set_image(Engine::Rendering::Image::Component & image,
         _float2 const &position, _float2 const& length, float angle =0);
    void set_image(Engine::Rendering::Image::UI & image,
         _float2 const& position, _float2 const& length, float angle = 0);

    //==================== Main Title ================
    void render_main_text(_float2 test_location, _float2 test_length);
    void render_main(_float2 test_location, _float2 test_length);

    //  ==================== Lobby ===================
    void render_tank_image(std::string const& name, _float2 const& position, _float2 const& length);

    //  ==================== Battle ==================
    
    //Battle(loading)
    void render_loading();

    //Battle(playing)
    void render_background();
    void render_minimap_background();
    void render_ui(std::vector<Tank> const& tank);
    void render_minimap_tank(std::vector<Tank> const& tank);
    void render_minimap_cambox();

    // Game Over 
    void render_gameover();

};
