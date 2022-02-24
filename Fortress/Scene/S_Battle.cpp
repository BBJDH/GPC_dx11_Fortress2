
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
    _Button->scene_buttons.erase("exit");
    _Tank->clear();
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
    pattern_name = pattern_name_list[rand()% list_size];
    state = State::Loading;
    playing_time = 0.0f;
    Camera.Sight = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    _Map_manager->initialize();
    _Tank->create_tanks();
    set_playing_exit_button();
    set_power_collide_box();
   
}

void S_Battle::set_playing_exit_button()
{
    _Button->scene_buttons.insert
    (
        {
            "exit",
             Button<Scene*>(std::bind(&Button_manager::to_lobby,_Button),"Battle/playing_exit")
        }
    );
    _Button->scene_buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));


    _Button->scene_buttons.at("exit").init_image_location({ playing_exit_x, playing_exit_y });
    _Button->scene_buttons.at("exit").init_image_size({playing_exit_w, playing_exit_h});
}

void S_Battle::set_gameover_exit_button()
{
    _Button->scene_buttons.insert
    (
        {
            "exit",
             Button<Scene*>(std::bind(&Button_manager::to_lobby,_Button),"Battle/gameover_exit")
        }
    );
    _Button->scene_buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));


    _Button->scene_buttons.at("exit").init_image_location({ gameover_exit_x, gameover_exit_y });
    _Button->scene_buttons.at("exit").init_image_size({ gameover_exit_w, gameover_exit_h });

}

void S_Battle::set_power_collide_box()
{
    _float2 pos = { 770 ,668 };
    _float2 length = { 650 ,20 };

    _Button->nomal_buttons.insert
    (
        {
            "guide",
             Button<bool>(std::bind(&Button_manager::set_power_guide,_Button),"Battle/guide")
        }
    );
    _Button->nomal_buttons.at("guide").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));

    _Button->nomal_buttons.at("guide").init_image_location({ pos.x, pos.y });
    _Button->nomal_buttons.at("guide").init_image_size({ length.x, length.y });

}



void S_Battle::create_pattern(std::string const& name)
{
    float const out_value = 50.0f;
    switch (static_cast<Side>(rand()%3))
    {
    case S_Battle::Side::Up:
    {
        patterns.push_back
        (
            Patterns
            (
                name,
                {
                    static_cast<float>(rand() % MAPSIZE_W),
                    -out_value
                }
            )
        );
        break;
    }
    case S_Battle::Side::Left:
    {
        patterns.push_back
        (
            Patterns
            (
                name,
                {
                    -out_value,
                    static_cast<float>(rand() % (MAPSIZE_H-100))
                }
            )
        );
        break;
    }
    case S_Battle::Side::Right:
    {
        patterns.push_back
        (
            Patterns
            (
                name,
                {
                    MAPSIZE_W + out_value,
                    static_cast<float>(rand() % (MAPSIZE_H - 100))
                }
            )
        );
        break;
    }
    default:
        break;
    }

    patterns.back().ballistics_initialize(0, 0);
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
        //TODO: 포스트 이펙트 블러(화면넘길때 사용)
        Engine::Rendering::Pipeline::Effect::set_y((playing_time/ min_loading_time)* CAM_SIZE_H);
        _Image_manager->render_loading();

        //애니메이션으로 로딩씬 그리기
        //_Anime->render_loading(Engine::Time::Get::Delta());
        if (playing_time > waiting_time)
        {
            dispose_objects();
            if (!_Turn->check_tank_falling(_Tank->tanks) and playing_time > min_loading_time)
            {
                _Anime->render_loading_end(Engine::Time::Get::Delta());
                if(_Anime->get_loading_time() < 0.1f and playing_time > min_loading_time+ 0.5f)
                {
                    Engine::Rendering::Pipeline::Effect::set_y(MAPSIZE_H+200); //UI사이즈만큼 더함
                    _Turn->tankturn_start(_Tank->tanks);
                    this->state = State::Playing;
                    break;
                }
            }
        }

        break;
    }
    case S_Battle::State::Playing:
    {

        _Turn->checkturn(_Tank->tanks,missile);	//턴체크후 다음턴 부여
        _Input_manager->input(_Tank->tanks,missile,patterns,Engine::Time::Get::Delta());

        dispose_objects();            //이동계산 및 충돌검사

        render_playing();            //렌더링

       
        if (_Turn->is_gameover(_Tank->tanks))
        {
            _Button->scene_buttons.erase("exit");
            _Button->nomal_buttons.erase("guide");
            this->state = State::GameOver;
        }
        _Button->render_buttons();
        for (auto iter = _Button->scene_buttons.begin(); iter != _Button->scene_buttons.end(); ++iter)
        {
            if (iter->second.clicked())	//상태에 따라 이벤트 처리
                return iter->second.execute();
        }
        return nullptr;
    }
    case S_Battle::State::GameOver:
    {
        set_gameover_exit_button();
        Camera.Location = { _CAM->pos.x,_CAM->pos.y };
        Camera.Set();
        _Image_manager->render_gameover();

        //버튼을 누르면 시작화면으로
        _Button->render_buttons();
        for (auto iter = _Button->scene_buttons.begin(); iter != _Button->scene_buttons.end(); ++iter)
        {
            if (iter->second.clicked())	//상태에 따라 이벤트 처리
                return iter->second.execute();
        }
        return nullptr;

    }
    break;
    default:
        break;
    }
    return nullptr;
}

void S_Battle::dispose_objects()
{
    float const delta = Engine::Time::Get::Delta();
    interval += delta;
    if (interval > pattern_gen_time)
    {
        create_pattern(pattern_name);
        interval = 0;
    }
    _Physics_manager->ballistics(_Tank->tanks,missile,patterns, delta);//이동계산과 낙하, 맵밖 삭제
    _Physics_manager->Collide_objects(_Tank->tanks,missile,_Map_manager->hmapdc);//계산한 자리에서 충돌 및 삭제 처리
}

void S_Battle::render_playing() //Update
{
    _CAM->update();
    Camera.Location = { _CAM->pos.x,_CAM->pos.y };
    Camera.Set();
    _Map_manager->render_map(patterns);

    _Anime->render(_Tank->tanks,missile);
    _Text_manager->render(_Tank->tanks);

    _Image_manager->render_ui(_Tank->tanks);

    _Map_manager->render_minimap(_Tank->tanks);


    //_Debug_manager->set_delta(Engine::Time::Get::Delta());
    //_Debug_manager->rendering();

    //타겟을 다 결합하고 한번에 다 그리는 방식
}
