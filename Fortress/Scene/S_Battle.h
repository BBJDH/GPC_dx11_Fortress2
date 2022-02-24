#pragma once


class S_Battle final : public Scene
{
public:
    enum class State 
    {
        Loading, Playing, GameOver,
    };
    enum class Side
    {   
        Up, Left, Right
    };
private:

    //std::vector<Object> obj;
    State state=State::Loading;
    std::vector<Missile> missile;
    std::vector<Patterns> patterns;
    Engine::Rendering::Camera Camera;
    std::string pattern_name;
    //로딩 설정
    float const min_loading_time = 4.0f;
    float const waiting_time = 1.0f; //기본 초기화 대기시간
    float const pattern_gen_time = 0.3f;
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

    //패턴 파일 이름
    std::string const pattern_name_list[2] = { "pinwheel","ufo" };
    unsigned const list_size = 2;
private:
    void    initialize();
    void    set_playing_exit_button();
    void    set_gameover_exit_button();
    void    set_power_collide_box();
    void    create_pattern(std::string const & name);
    void    dispose_objects();
    void    render_playing();
    
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    Scene *   update_scene();


};