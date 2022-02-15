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

private:
    bool    toggle_slot_button();
    void    set_exit_button();
    void    set_start_button();
    void    set_slot_button(std::string const& button_name,
        float const start_x, float const start_y, float const start_w, float const start_h);
    void    set_slot_buttons();
    void    init_image();
    void    render();
    

public:
    bool    check_start_button();
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
};

//슬롯 버튼을 누르고 캐릭터버튼을 누르면 슬롯에 캐릭터가 올라옴
//슬롯의 캐릭터를 누르면 해당 슬롯 해제