
#include"stdafx.h"


void Fortress::Start()
{
    //_Image_manager->initialize();

    Now = new S_Start;

    Now->Start();
}

void Fortress::Update()
{
    Scene * const Next = Now->Update();

    _Mouse->x = Engine::Input::Get::Cursor::X();
    _Mouse->y = Engine::Input::Get::Cursor::Y();
    _Mouse->convert_coodinate();
    
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



Engine::Game * Engine::Initialize()
{
    return new Fortress();
}