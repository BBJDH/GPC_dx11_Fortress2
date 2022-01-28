#pragma once


class S_Battle final : public Scene
{
public:
    enum class State 
    {
        Loading, Playing, GameOver,
    };
private:

    //std::vector<Object> obj;
    State state;
    std::vector<Tank> tank;
    std::vector<Missile> missile;
    Engine::Rendering::Camera Camera;

private:
    void    rendering();

public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    void    set_state(State const state);


};