#pragma once
class S_Lobby final : public Scene
{
private:
    Engine::Rendering::Image::UI lobby;


private:

    
    //버튼설정
    float const exit_x = 1150;
    float const exit_y = 690;
    float const exit_w = 170;
    float const exit_h = 30;

    float const start_x = 100;
    float const start_y = 690;
    float const start_w = 170;
    float const start_h = 30;

    float const tank_button_location_x = 70;
    float const tank_button_location_y = 552;
    float const tank_button_width = 80;
    float const tank_button_heght = 50;
    float const tank_button_offset_x = tank_button_width + 18;
    float const tank_button_offset_y = tank_button_heght + 18;

private:
    void    set_exit_button();
    void    set_start_button();
    void    set_slot_button(std::map<std::string, Button<bool>> & slot_button,
        std::string const& button_name, std::string const& location,
        float const start_x, float const start_y, float const start_w, float const start_h);

    void    set_slot_buttons();
    void    set_tank_buttons();
    void    render_tank_button_image();
    void    render_tank_selected();
    void    render_slot_color();
    void    render_slot_text();
    void    render_button_images();
    void    init_image();
    void    render();
    

public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
};

//슬롯 버튼을 누르고 캐릭터버튼을 누르면 슬롯에 캐릭터가 올라옴
//슬롯의 캐릭터를 누르면 해당 슬롯 해제