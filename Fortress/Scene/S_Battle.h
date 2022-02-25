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
    //�ε� ����
    float const min_loading_time = 4.0f;
    float const waiting_time = 1.0f; //�⺻ �ʱ�ȭ ���ð�
    float const pattern_gen_time = 0.3f;
    float playing_time=0.0f;
    float interval=0.0;
    
private:


    //���� ���� �̸�
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