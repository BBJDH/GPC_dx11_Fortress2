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
    Button<Scene*> * exit_button;


private:
    //버튼설정
    float const playing_exit_x = 1200;
    float const playing_exit_y = 705;
    float const playing_exit_w = 130;
    float const playing_exit_h = 18;

    float const gameover_exit_x = 1180;
    float const gameover_exit_y = 697;
    float const gameover_exit_w = 170;
    float const gameover_exit_h = 30;


    float const waiting_time = 2.0f;
    float playing_time;
private:
    void    initialize();
    void    set_playing_exit_button();
    void    set_gameover_exit_button();
    void    create_tanks();
    void    dispose_tanks();
    void    render_playing();
    
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    Scene *   update_scene();


};