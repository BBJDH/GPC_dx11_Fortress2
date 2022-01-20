
#include"stdafx.h"


void Fortress::Start()
{
    Now = new S_Battle;

    Now->Start();
}

void Fortress::Update()
{
    Scene * const Next = Now->Update();

    _Mouse->x = Engine::Input::Get::Cursor::X();
    _Mouse->y = Engine::Input::Get::Cursor::Y();

    Input();
    if(!obj.empty())
        obj.back().ballistics_equation(Engine::Time::Get::Delta());
    //LONG x =   _Mouse->x;
    //LONG y =   _Mouse->y;
    
    if(Next != nullptr)
    {
        Now->End();

        delete Now;

        Now = Next;

        Now->Start();
    }


}

void Fortress::End()
{
    Now->End();

    delete Now;
}

void Fortress::Input()
{
    if (Engine::Input::Get::Key::Press(VK_LBUTTON))
    {
        float x = static_cast<float>(_Mouse->x);
        float y = static_cast<float>(_Mouse->y);
        obj.push_back(Object({0,0},	49,	42));
        obj.back().ballistics_initialize(0, 0);
        

    }
}

Engine::Game * Engine::Initialize()
{
    return new Fortress();
}