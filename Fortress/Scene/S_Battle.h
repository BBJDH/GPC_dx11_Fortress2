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
    Button exit_button;


    float const waiting_time = 2.0f;
    float playing_time;
private:
    void    initialize();
    void    create_tanks();
    void    dispose_tanks();
    void    render_playing();
    
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    Scene *   update_scene();


};