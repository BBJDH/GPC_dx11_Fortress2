
#include"stdafx.h"


void Fortress::Start()
{
    Now = new S_Battle;

    Now->Start();
}

void Fortress::Update()
{
    Scene * const Next = Now->Update();



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