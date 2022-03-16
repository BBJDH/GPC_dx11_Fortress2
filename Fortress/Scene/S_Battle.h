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
    //Engine::Rendering::Camera Camera;
    float playing_time;

    //�ε� ����
    float const min_loading_time = 4.0f;
    float const waiting_time = 1.0f; //�⺻ �ʱ�ȭ ���ð�

    //���� �� ����
    
private:


    //���� ���� �̸�
private:
    void    initialize();
    //void    create_pattern(std::string const & name);
    void    dispose_objects();
    void    render_playing();
    
public:
    void     Start() final override;
    Scene * Update() final override;
    void       End() final override;
    Scene *   update_scene();


};