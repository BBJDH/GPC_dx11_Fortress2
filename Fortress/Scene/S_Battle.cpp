
#include "stdafx.h"
#include "S_Battle.h"



void S_Battle::Start()
{
    initialize();

}

Scene * S_Battle::Update()
{   
    playing_time += Engine::Time::Get::Delta();

    return update_scene();
}

void S_Battle::End()
{
    delete exit_button;
    tank.clear();
    std::vector<Tank>().swap(tank);
    missile.clear();
    std::vector<Missile>().swap(missile);


    _Anime->release_singleton();
    _Input_manager->release_singleton();
    _Turn->release_singleton();
    _Map_manager->release_singleton();
    _Physics_manager->release_singleton();
    _Debug_manager->release_singleton();
    _CAM->release_singleton();
}


void S_Battle::initialize()
{
    srand(static_cast<unsigned>(time(NULL)));
    state = State::Loading;
    playing_time = 0.0f;
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    create_tanks();


    exit_button = new Button(_Button->bind_function<Scene*>(Button_manager::Func::Exit));
    set_playing_exit_button();
}

void S_Battle::set_playing_exit_button()
{
    exit_button->image.Name = "Image/Button/playing_exit";
    exit_button->image.Length =  Vector<2>(playing_exit_w, playing_exit_h);
    exit_button->image.Location = Vector<2>(playing_exit_x, playing_exit_y);
    exit_button->collide_image.Name = "Image/Button/playing_exit_collide";
    exit_button->collide_image.Length =  Vector<2>(playing_exit_w, playing_exit_h);
    exit_button->collide_image.Location = Vector<2>(playing_exit_x, playing_exit_y);
    exit_button->collide_box.Length = Point{playing_exit_w,playing_exit_h};
    exit_button->collide_box.Center = Point{playing_exit_x,playing_exit_y};
}

void S_Battle::set_gameover_exit_button()
{
    exit_button->image.Name = "Image/Button/gameover_exit";
    exit_button->image.Length =  Vector<2>(gameover_exit_w, gameover_exit_h);
    exit_button->image.Location = Vector<2>(gameover_exit_x, gameover_exit_y);
    exit_button->collide_image.Name = "Image/Button/gameover_exit_collide";
    exit_button->collide_image.Length =  Vector<2>(gameover_exit_w, gameover_exit_h);
    exit_button->collide_image.Location = Vector<2>(gameover_exit_x, gameover_exit_y);
    exit_button->collide_box.Length = Point{gameover_exit_w,gameover_exit_h};
    exit_button->collide_box.Center = Point{gameover_exit_x,gameover_exit_y};
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


Scene * S_Battle::update_scene()
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

        render_playing();            //렌더링

        if(exit_button->clicked())
            return exit_button->execute();
        if (_Turn->is_gameover(tank))
            this->state = State::GameOver;
        break;
    }
    case S_Battle::State::GameOver:
    {
        set_gameover_exit_button();
        Camera.Location = { _CAM->pos.x,_CAM->pos.y };
        Camera.Set();
        _Image_manager->render_gameover();

        //버튼을 누르면 시작화면으로
        if(exit_button->clicked())
            return exit_button->execute();
    }
    break;
    default:
        break;
    }
    return nullptr;
}


void S_Battle::dispose_tanks()
{
    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());
    _Physics_manager->Collide_objects(tank,missile,_Map_manager->hmapdc);
}


void S_Battle::render_playing()
{

    //Engine::Rendering::Pipeline::Effect::set_alhpa(abs(sin(playing_time)));
    //Engine::Rendering::Pipeline::Effect::set_alhpa(1.0f);

    _Image_manager->render_background();
    _Map_manager->render_map();

    _Anime->render(tank,missile);
    _Image_manager->render_ui(tank);
    _Map_manager->render_minimap();
    _Image_manager->render_minimap_tank(tank);


    _Debug_manager->set_delta(Engine::Time::Get::Delta());
    _Debug_manager->rendering();

}
