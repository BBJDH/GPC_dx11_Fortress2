#include "Game.h"

#include "Stage1.h"

void Game::Start()
{
    Now = new Stage1;

    Now->Start();
}

void Game::Update()
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

void Game::End()
{
    Now->End();

    delete Now;
}

Engine::Game * Engine::Initialize()
{
    return new ::Game();
}