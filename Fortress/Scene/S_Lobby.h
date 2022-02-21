#pragma once
class S_Lobby final : public Scene
{
private:

    void    render_slot_base();
    void    render_tank_selected();
    void    render_slot_color();
    void    render_slot_text();
    void    render_button_images();
    void    render();
    

public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
};

//슬롯 버튼을 누르고 캐릭터버튼을 누르면 슬롯에 캐릭터가 올라옴
//슬롯의 캐릭터를 누르면 해당 슬롯 해제