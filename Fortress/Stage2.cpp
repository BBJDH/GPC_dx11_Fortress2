#include "Stage2.h"

#include "Engine/Input.h"
#include "Player.h"

void Stage2::Start()
{    
    {
        Background.Name = "Image/Map";

        Background.Length = Vector<2>(2400, 1500);
    }
    {
        Sonic = new Player;

        Sonic->Start();
    }
}

Scene * Stage2::Update()
{
    Background.Render();
    
    Sonic->Update();

    return nullptr;
}

void Stage2::End()
{
    Sonic->End();

    delete Sonic;
}