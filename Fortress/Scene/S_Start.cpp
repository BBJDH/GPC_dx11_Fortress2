#include "stdafx.h"
#include "S_Start.h"


void S_Start::render_text()
{

    text_width  += speed_x *sin(time*PI);
    text_height += speed_y *sin(time*PI);
    _Image_manager->render_main_text
    (
        { CAM_SIZE_W / 2, (CAM_SIZE_H / 2) + TEXT_Location_Y },
        { text_width,text_height }
    );

}

bool S_Start::Enter()
{
    if(Engine::Input::Get::Key::Down(VK_RETURN))
        return true;
    return false;
}

void S_Start::render()
{
    time += Engine::Time::Get::Delta();
    _Image_manager->render_main
    (
        { CAM_SIZE_W / 2, CAM_SIZE_H / 2 },
        { CAM_SIZE_W, CAM_SIZE_H }
    );
    render_text();
}

void S_Start::Start()
{
    Engine::Rendering::Pipeline::Effect::set_y(CAM_SIZE_H);
    text_width = TEXT_W;
    text_height = TEXT_H;
}

Scene* S_Start::Update()
{
    //Engine::Rendering::Pipeline::Effect::set_alhpa(abs(sin(time)));

    render();
    if(Enter())
        return new S_Lobby;

    return nullptr;
}

void S_Start::End()
{
}
