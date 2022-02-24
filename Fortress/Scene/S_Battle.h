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
    State state=State::Loading;
    std::vector<Tank> tank;
    std::vector<Missile> missile;
    std::vector<Patterns> patterns;
    Engine::Rendering::Camera Camera;

    //로딩 설정
    float const min_loading_time = 4.0f;
    float const waiting_time = 2.0f; //기본 초기화 대기시간
    float const pattern_gen_time = 0.5f;
    float playing_time=0.0f;
    float interval=0.0;
    
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



private:
    void    initialize();
    void    set_playing_exit_button();
    void    set_gameover_exit_button();
    void    create_tanks();
    void    dispose_objects();
    void    render_playing();
    
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    Scene *   update_scene();


};