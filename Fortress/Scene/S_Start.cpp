#include "stdafx.h"
#include "S_Start.h"

void S_Start::init_image()
{
    text_width  = TEXT_W;
    text_height = TEXT_H;
    fortress.Name = "Image/Screen/start";
    fortress.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    fortress.Location = Vector<2>(CAM_SIZE_W / 2, CAM_SIZE_H / 2);

    text.Name = "Image/Text/start_text2";
    text.Length = Vector<2>(text_width, text_height);
    text.Location = Vector<2>(CAM_SIZE_W / 2 , (CAM_SIZE_H / 2)+TEXT_Location_Y);
    
}

void S_Start::render_text()
{
    //if (static_cast<int>(time) % 2)
    //{
    //    text_width  = text_width +0.05f;
    //    text_height = text_height+0.01f;
    //}
    //else
    //{
    //    text_width  = text_width -0.05f;
    //    text_height = text_height-0.01f;
    //}
    text_width  += speed_x *sin(time*PI);
    text_height += speed_y *sin(time*PI);
    text.Length = Vector<2>(text_width, text_height);
    text.Render();
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
    fortress.Render();
    render_text();
}

void S_Start::Start()
{
    init_image();
}

Scene* S_Start::Update()
{
    render();
    if(Enter())
        return new S_Battle;

    return nullptr;
}

void S_Start::End()
{
}
