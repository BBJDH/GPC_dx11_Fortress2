
#include "stdafx.h"
#include "../stdafx.h"
#include "S_Battle.h"



void S_Battle::Start()
{
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
}

Scene * S_Battle::Update()
{   
    using namespace Engine;
    
    _CAM->move(_Mouse->getstate()); //마우스 위치에 따라 카메라 이동


    if (Engine::Input::Get::Key::Press(VK_LBUTTON))
    {
        float x = static_cast<float>(_Mouse->x);
        float y = static_cast<float>(_Mouse->y);
        tank.push_back(Tank({(_CAM->pos.x) + _Mouse->coordinate_x,(_CAM->pos.y) + _Mouse->coordinate_y},	49,	42));
        tank.back().ballistics_initialize(0, 0);
    }
    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());

    rendering();            //렌더링
    return nullptr;
}

void S_Battle::End()
{

}

void S_Battle::rendering()
{
    _Image_manager->render_background();
    _Image_manager->render_map();

    //탱크 미사일 아이템 등 그리기
    _Image_manager->render_tank(tank);

    _Image_manager->render_back_ui();
    _Image_manager->render_front_ui();
    Camera.Location = { _CAM->pos.x,_CAM->pos.y };
    Camera.Set();


    _Debug_manager->rendering();

}
