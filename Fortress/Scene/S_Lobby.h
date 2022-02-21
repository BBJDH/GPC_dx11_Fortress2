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

//���� ��ư�� ������ ĳ���͹�ư�� ������ ���Կ� ĳ���Ͱ� �ö��
//������ ĳ���͸� ������ �ش� ���� ����