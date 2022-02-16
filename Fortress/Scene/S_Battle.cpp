
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
    _Button->buttons.erase("exit");
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

    set_playing_exit_button();
}

void S_Battle::set_playing_exit_button()
{
    _Button->buttons.insert
    (
        {
            "exit",
             Button<Scene*>(std::bind(&Button_manager::to_lobby,_Button),"playing_exit")
        }
    );
    _Button->buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));


    _Button->buttons.at("exit").init_image_location(playing_exit_x, playing_exit_y);
    _Button->buttons.at("exit").init_image_size(playing_exit_w, playing_exit_h);
}

void S_Battle::set_gameover_exit_button()
{
    _Button->buttons.insert
    (
        {
            "exit",
             Button<Scene*>(std::bind(&Button_manager::to_lobby,_Button),"gameover_exit")
        }
    );
    _Button->buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));


    _Button->buttons.at("exit").init_image_location(gameover_exit_x, gameover_exit_y);
    _Button->buttons.at("exit").init_image_size(gameover_exit_w, gameover_exit_h);

}

void S_Battle::create_tanks()
{
    //Random r(10, MAPSIZE_W - 10, PLAYERS);
    int const rand_mul = MAPSIZE_W / PLAYERS; //플레이어수만큼 구역을 나누고 좌우 10픽셀 만큼 좁힌다
    Random r(0, PLAYERS-1,PLAYERS);
    for (unsigned i = 0; i < PLAYERS; i++)
    {
        //float const loc_x = static_cast<float>(r.GetResult(i));
        float const loc_x = (static_cast<float>(r.GetResult(i) * rand_mul + (rand() % rand_mul)+10) );
        tank.push_back(Tank({loc_x, 0}, Tank_SIZE, Tank_SIZE, "player " + std::to_string(i + 1)));
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
        
        //셰이더로 로딩씬 그리기
        //포스트 이펙트 블러
        Engine::Rendering::Pipeline::Effect::set_y((playing_time/ min_loading_time)* CAM_SIZE_H);
        _Image_manager->render_loading();

        //애니메이션으로 로딩씬 그리기
        //_Anime->render_loading(Engine::Time::Get::Delta());
        if (playing_time > waiting_time)
        {
            dispose_objects();
            if (!_Turn->check_tank_falling(tank) and playing_time > min_loading_time)
            {
                _Anime->render_change_loading(Engine::Time::Get::Delta());
                if(_Anime->get_loading_time() < 0.1f and playing_time > min_loading_time+ 0.5f)
                {
                    Engine::Rendering::Pipeline::Effect::set_y(MAPSIZE_H);
                    _Turn->tankturn_start(tank);
                    this->state = State::Playing;
                    break;
                }
            }
        }

        break;
    }
    case S_Battle::State::Playing:
    {
        Camera.Location = { _CAM->pos.x,_CAM->pos.y };
        Camera.Set();
        _CAM->cam();

        _Turn->checkturn(tank,missile);	//턴체크후 다음턴 부여
        _Input_manager->input(tank,missile,Engine::Time::Get::Delta());

        dispose_objects();            //이동계산 및 충돌검사

        render_playing();            //렌더링

       
        if (_Turn->is_gameover(tank))
        {
            _Button->buttons.erase("exit");
            this->state = State::GameOver;
        }
        return _Button->click_buttons();
    }
    case S_Battle::State::GameOver:
    {
        set_gameover_exit_button();
        Camera.Location = { _CAM->pos.x,_CAM->pos.y };
        Camera.Set();
        _Image_manager->render_gameover();

        //버튼을 누르면 시작화면으로
        return _Button->click_buttons();

    }
    break;
    default:
        break;
    }
    return nullptr;
}

void S_Battle::dispose_objects()
{
    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());//이동계산과 낙하, 맵밖 삭제
    _Physics_manager->Collide_objects(tank,missile,_Map_manager->hmapdc);//계산한 자리에서 충돌 및 삭제 처리
}

void S_Battle::render_playing() //Update
{
    _Map_manager->render_map();

    _Anime->render(tank,missile);
    _Text_manager->render(tank);

    _Image_manager->render_ui(tank);

    _Map_manager->render_minimap(tank);   

    //_Debug_manager->set_delta(Engine::Time::Get::Delta());
    //_Debug_manager->rendering();

    //타겟을 다 결합하고 한번에 다 그리는 방식
}
