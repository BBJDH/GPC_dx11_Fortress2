#pragma once
class S_Lobby final : public Scene
{
private:
    void    render();

public:
    void     Start() final override;
    Scene* Update() final override;
    void       End() final override;
};

//���� ��ư�� ������ ĳ���͹�ư�� ������ ���Կ� ĳ���Ͱ� �ö��
//������ ĳ���͸� ������ �ش� ���� ����