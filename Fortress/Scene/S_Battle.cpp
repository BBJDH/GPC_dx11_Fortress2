
#include "S_Battle.h"
#include"stdafx.h"
//#include "Stage2.h"

//#include "Engine/Input.h"


void S_Battle::Start()
{


    Background.Name = "Image/background";
    Background.Length = Vector<2>(BackgroundSIZE_W, BackgroundSIZE_H) ;
    Map.Name = "Image/Sky";
    Map.Length = Vector<2>(MAPSIZE_W, MAPSIZE_H) ;
    UI_Back.Name = "Image/UI_Back";
    UI_Back.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H) ;
    UI_Back.Location = Vector<2>(CAM_SIZE_W/2, CAM_SIZE_H/2); //윈도우 좌표계 좌측상단 0,0 기준
    UI_Front.Name = "Image/UI_Front";
    UI_Front.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H) ;
    UI_Front.Location = Vector<2>(CAM_SIZE_W/2, CAM_SIZE_H/2); //윈도우 좌표계 좌측상단 0,0 기준

    
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    

    //debug_mouse_x.Text = "디버그"; //"디버그";// 
    //debug_mouse_x.Font.Name = "Kostar";
    //debug_mouse_x.Font.Size = 20;
    //debug_mouse_x.Font.Bold = false;
    //debug_mouse_x.Font.Italic = false;
    //debug_mouse_x.Font.Underlined = false;
    //debug_mouse_x.Font.StructOut = false;
    //debug_mouse_x.Color.Red = 255;
    //debug_mouse_x.Color.Blue = 255;
    //debug_mouse_x.Color.Green = 255;
    //debug_mouse_x.Length = { 350, 150 };
    //debug_mouse_x.Location = { _CAM->pos.x+200,  100 };

    
}

Scene * S_Battle::Update()
{
    using namespace Engine;

    _CAM->move(_Mouse->getpos()); //마우스 위치에 따라 카메라 이동

    rendering();            //렌더링


    return nullptr;
}

void S_Battle::End()
{

}

void S_Battle::rendering()
{
    Background.Render();
    Map.Render();
    UI_Back.Render();
    UI_Front.Render();
    Camera.Location = { _CAM->pos.x,_CAM->pos.y };
    Camera.Set();
}
