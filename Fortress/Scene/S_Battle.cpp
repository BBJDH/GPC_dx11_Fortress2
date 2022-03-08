
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
    _Button->clear_buttons();
    _Tank->release_singleton();
    _Missile->release_singleton();
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
    interval = 0.0;
    _CAM->init_camera();
    _Map_manager->initialize();
    _Tank->create_tanks();
    _Button->init_battle_buttons();
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

    }

    patterns.back().ballistics_initialize(0, 0);
}


Scene * S_Battle::update_scene()
{
    switch (this->state)
    {
    case S_Battle::State::Loading:
    {
        float const fadeout_time = 0.5f;
        _CAM->init_camera();

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
                _Anime->render_loading_fade_out(Engine::Time::Get::Delta());
                if( playing_time > min_loading_time + fadeout_time)
                {
                    Engine::Rendering::Pipeline::Effect::set_y(MAPSIZE_H+200); //UI사이즈만큼 더함
                    _Turn->tankturn_start(*_Tank->tanks[_Turn->whosturn()]);
                    this->state = State::Playing;
                    break;
                }
            }
        }

        break;
    }
    case S_Battle::State::Playing:
    {
        _Turn->checkturn(_Tank->tanks, _Missile->missiles,_Effect->effects);	//턴체크후 다음턴 부여
        _Input_manager->input(_Tank->tanks, _Missile->missiles,patterns,Engine::Time::Get::Delta());
        dispose_objects();            //이동계산 및 충돌검사, 무늬 생성
        render_playing();            //렌더링
       
        if (_Turn->is_gameover(_Tank->tanks))
        {
            _Button->clear_buttons();
            this->state = State::GameOver;
        }
        return _Button->scene_button_on();
    }
    case S_Battle::State::GameOver:
    {

        _CAM->init_camera();
        _Button->init_gameover_exit_button();
        _Image_manager->render_gameover();
        _Button->render();

        //버튼을 누르면 시작화면으로
        return _Button->scene_button_on();
    }

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
    _Physics_manager->ballistics(_Tank->tanks, _Missile->missiles,patterns, delta);
    //이동계산 후 맵영역 이탈한 오브젝트를 delete state 기록 (문양은 별도 처리없이 바로 삭제)
    _Physics_manager->Collide_objects(_Tank->tanks, _Missile->missiles,_Map_manager->hmapdc);
    //충돌검사 및 데미지계산, 없어지는 인스턴스 delete state 기록 
}

void S_Battle::render_playing() //Update
{
    _CAM->update();
    _Map_manager->render_map(patterns); //배경 -> 패턴 -> 맵
    _Anime->render(_Tank->tanks, _Missile->missiles, _Effect->effects);  // 탱크 -> 미사일 -> 이펙트
    _Text_manager->render(_Tank->tanks);
    _Image_manager->render_ui(_Tank->tanks);
    _Map_manager->render_minimap(_Tank->tanks);
    _Button->render_battle_button();


    //_Debug_manager->set_delta(Engine::Time::Get::Delta());
    //_Debug_manager->rendering();

}
