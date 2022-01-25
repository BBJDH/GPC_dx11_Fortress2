
#include "stdafx.h"
#include "S_Battle.h"



void S_Battle::Start()
{
    _Map_manager->initialize();
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);

    srand(static_cast<unsigned>(time(NULL)));
    Random r(10,MAPSIZE_W-10,PLAYERS);
    for (unsigned i = 0; i < PLAYERS; i++)
    {
        tank.push_back(Tank({ static_cast<float>(r.GetResult(i)),0 }, Tank_SIZE, Tank_SIZE));
        tank.back().ballistics_initialize(0, 0);
    }

}

Scene * S_Battle::Update()
{   
    using namespace Engine;
    
    _CAM->move(_Mouse->getstate()); //마우스 위치에 따라 카메라 이동


    _Turn->checkturn(tank,missile);	//턴체크후 다음턴 부여
    _Input_manager->input(tank,missile,Time::Get::Delta());

    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());
    _Physics_manager->Collide_objects(tank,missile,_Map_manager->hmapdc);

    rendering();            //렌더링
    return nullptr;
}

void S_Battle::End()
{

}

void S_Battle::rendering()
{
    _Image_manager->render_background();
    _Map_manager->render_map();

    //탱크 미사일 아이템 등 그리기
    _Image_manager->render_tank(tank);
    _Image_manager->render_missile(missile);

    _Image_manager->render_back_ui(tank[_Turn->whosturn()]);
    _Image_manager->render_front_ui(tank[_Turn->whosturn()]);
    Camera.Location = { _CAM->pos.x,_CAM->pos.y };
    Camera.Set();

    _Debug_manager->set_delta(Engine::Time::Get::Delta());
    _Debug_manager->rendering();

}
