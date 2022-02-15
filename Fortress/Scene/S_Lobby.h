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
    void    set_exit_button();
    void    set_start_button();
    void    init_image();
    void    render();

public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
};

//슬롯 버튼을 누르고 캐릭터버튼을 누르면 슬롯에 캐릭터가 올라옴
//슬롯의 캐릭터를 누르면 해당 슬롯 해제