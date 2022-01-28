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

// TODO: 게임종료 씬 띄우기, 로딩화면 띄우기,시작화면 띄우기