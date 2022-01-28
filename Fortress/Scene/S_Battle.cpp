
#include "stdafx.h"
#include "S_Battle.h"



void S_Battle::Start()
{
    initialize();
    _Turn->tankturn_start(tank);
}

Scene * S_Battle::Update()
{   
    playing_time += Engine::Time::Get::Delta();

    update_scene();

    return nullptr;
}

void S_Battle::End()
{
    tank.clear();
    std::vector<Tank>().swap(tank);
    missile.clear();
    std::vector<Missile>().swap(missile);
}


void S_Battle::initialize()
{
    srand(static_cast<unsigned>(time(NULL)));
    state = State::Loading;
    playing_time = 0.0f;
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    create_tanks();
}

void S_Battle::create_tanks()
{
    Random r(10,MAPSIZE_W-10,PLAYERS);
    for (unsigned i = 0; i < PLAYERS; i++)
    {
        tank.push_back(Tank({ static_cast<float>(r.GetResult(i)),0 }, Tank_SIZE, Tank_SIZE));
        tank.back().ballistics_initialize(0, 0);
    }
}


void S_Battle::update_scene()
{
    switch (this->state)
    {
    case S_Battle::State::Loading:
    {
        Camera.Location = { 0,0 };
        Camera.Set();

        if (playing_time > waiting_time)
        {
            dispose_tanks();
            if(!_Turn->check_tank_falling(tank) and _Anime->get_loading_time()<0.1f)
                this->state = State::Playing;
        }
        _Anime->render_loading(Engine::Time::Get::Delta());

        break;
    }
    case S_Battle::State::Playing:
    {
        Camera.Location = { _CAM->pos.x,_CAM->pos.y };
        Camera.Set();
        _CAM->cam();

        _Turn->checkturn(tank,missile);	//턴체크후 다음턴 부여
        _Input_manager->input(tank,missile,Engine::Time::Get::Delta());

        dispose_tanks();

        rendering();            //렌더링

        break;
    }
    case S_Battle::State::GameOver:
        break;
    default:
        break;
    }
}


void S_Battle::dispose_tanks()
{
    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());
    _Physics_manager->Collide_objects(tank,missile,_Map_manager->hmapdc);
}


void S_Battle::rendering()
{
    _Image_manager->render_background();
    _Map_manager->render_map();

    _Anime->render(tank,missile);
    _Image_manager->render_ui(tank);

    _Debug_manager->set_delta(Engine::Time::Get::Delta());
    _Debug_manager->rendering();
}
