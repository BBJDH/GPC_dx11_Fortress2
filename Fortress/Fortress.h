#pragma once


class Fortress final : public Engine::Game
{
public:
    void  Start() final override;
    void Update() final override;
    void    End() final override;
    void Input();

private:
    class Scene * Now = nullptr;
    std::vector<Object> obj;
    //std::vector<Tank> tank;
    //std::vector<Missile> missile;
    //Random rand_turn;
};