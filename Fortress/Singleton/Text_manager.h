#pragma once
#include"SingletonT.h"


class Text_manager : public SingletonT<Text_manager>
{
public:

private:

    float delta=0.0f;
    Engine::Rendering::Text::Component fps;

    //========================  좌표  ==========================//
    //마우스의 윈도우좌표
    Engine::Rendering::Text::Component angle;



    void init_text(Engine::Rendering::Text::Component &text ,
        int const text_location_x,int const text_location_y);
    void render_text(Engine::Rendering::Text::Component &text, std::string const&str_value);

public:
    Text_manager();
    void set_delta(float const delta);
    void initialize();
    void rendering();

};