#include <Windows.h>

#include "Scene_Battle.h"
//#include "Stage2.h"

//#include "Engine/Input.h"
//#include "Player.h"

void Stage1::Start()
{

    {
        Background.Name = "Image/Fortress";

        Background.Length = Vector<2>(960, 703) * 4;
    }
   
}

Scene * Stage1::Update()
{
    using namespace Engine;

    Background.Render();


    return nullptr;
}

void Stage1::End()
{

}