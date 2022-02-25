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
    State state;
    std::vector<Patterns> patterns;
    //Engine::Rendering::Camera Camera;
    std::string pattern_name;
    float playing_time;
    float interval;

    //로딩 설정
    float const min_loading_time = 4.0f;
    float const waiting_time = 1.0f; //기본 초기화 대기시간

    //무늬 젠 간격
    float const pattern_gen_time = 0.3f;
    
private:


    //패턴 파일 이름
    std::string const pattern_name_list[2] = { "pinwheel","ufo" };
    unsigned const list_size = 2;
private:
    void    initialize();
    void    create_pattern(std::string const & name);
    void    dispose_objects();
    void    render_playing();
    
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    Scene *   update_scene();


};