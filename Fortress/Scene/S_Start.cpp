#include "stdafx.h"
#include "S_Start.h"

void S_Start::init_image()
{
    fortress.Name = "Image/Screen/start";
    fortress.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    fortress.Location = Vector<2>(CAM_SIZE_W / 2, CAM_SIZE_H / 2);

    
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
    if( static_cast<int>(time)%2)
        int i =0;// TODO : 텍스트 이미지 넣기

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
