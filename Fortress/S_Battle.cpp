
#include "S_Battle.h"
#include"stdafx.h"
//#include "Stage2.h"

//#include "Engine/Input.h"


void S_Battle::Start()
{


    Background.Name = "Image/Fortress";
    Background.Length = Vector<2>(1280, 720) ;
    Map.Name = "Image/Sky";
    Map.Length = Vector<2>(1280, 720) ;

    
    Camera.Sight = Vector<2>(1280, 720);
    
}

Scene * S_Battle::Update()
{
    using namespace Engine;

    Background.Render();
    Map.Render();
    Camera.Set();

    return nullptr;
}

void S_Battle::End()
{

}