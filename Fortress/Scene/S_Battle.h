#pragma once


class S_Battle final : public Scene
{
private:

    //std::vector<Object> obj;
    std::vector<Tank> tank;
    std::vector<Missile> missile;
    //Random rand_turn;
    Engine::Rendering::Camera Camera;

private:
    void    rendering();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;



};