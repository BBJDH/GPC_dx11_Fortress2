
#include "stdafx.h"
#include "S_Battle.h"



void S_Battle::Start()
{
    //_Map_manager->initialize();
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    //���� �ʱ�ȭ �Լ�(�ð����̺�)
    srand(static_cast<unsigned>(time(NULL)));//���ϸ� ���� ������ �׻� �Ȱ���
    Random r(10,MAPSIZE_W-10,PLAYERS);
    for (unsigned i = 0; i < PLAYERS; i++)
    {
        tank.push_back(Tank({ static_cast<float>(r.GetResult(i)),0 }, Tank_SIZE, Tank_SIZE));
        tank.back().ballistics_initialize(0, 0);
    }
    _Turn->tankturn_start(tank);
}

Scene * S_Battle::Update()
{   
    _CAM->cam();

    _Turn->checkturn(tank,missile);	//��üũ�� ������ �ο�
    _Input_manager->input(tank,missile,Engine::Time::Get::Delta());

    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());
    _Physics_manager->Collide_objects(tank,missile,_Map_manager->hmapdc);

    rendering();            //������

    return nullptr;
}

void S_Battle::End()
{

}

void S_Battle::rendering()
{
    Camera.Location = { _CAM->pos.x,_CAM->pos.y };
    Camera.Set();

    _Image_manager->render_background();
    _Map_manager->render_map();


    _Anime->render(tank,missile);
    _Image_manager->render_ui(tank);



    _Debug_manager->set_delta(Engine::Time::Get::Delta());
    _Debug_manager->rendering();

}
