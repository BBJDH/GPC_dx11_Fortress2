#pragma once


class Fortress final : public Engine::Game
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;

private:
    class Scene * Now = nullptr;
};

// TODO:  
// �̻��� ������ ��°� �����ϱ�,
