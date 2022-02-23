
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
    _Map_manager->initialize();
    create_tanks();
    set_playing_exit_button();
}

void S_Battle::set_playing_exit_button()
{
    _Button->scene_buttons.insert
    (
        {
            "exit",
             Button<Scene*>(std::bind(&Button_manager::to_lobby,_Button),"playing_exit")
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
             Button<Scene*>(std::bind(&Button_manager::to_lobby,_Button),"gameover_exit")
        }
    );
    _Button->scene_buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));


    _Button->scene_buttons.at("exit").init_image_location({ gameover_exit_x, gameover_exit_y });
    _Button->scene_buttons.at("exit").init_image_size({ gameover_exit_w, gameover_exit_h });

}

void S_Battle::create_tanks()
{
    //unsigned player = PLAYERS;
    unsigned player = static_cast<unsigned>(_Button->player_set.size());
    //Random r(10, MAPSIZE_W - 10, PLAYERS);
    int const rand_mul = MAPSIZE_W / player; //�÷��̾����ŭ ������ ������ �¿� 10�ȼ� ��ŭ ������
    Random r(0, player -1, player);
    for (unsigned i = 0; i < player; i++)
    {
        //float const loc_x = static_cast<float>(r.GetResult(i));
        float const loc_x = (static_cast<float>(r.GetResult(i) * rand_mul + (rand() % rand_mul)+10) );
        tank.push_back
        (
            Tank
            (
                {loc_x, 0},
                Tank_SIZE,
                Tank_SIZE,
                "player " + std::to_string(i + 1),
                std::get<2>(_Button->player_set[i])
            )
        );
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
        //���̴��� �ε��� �׸���
        //TODO: ����Ʈ ����Ʈ ��(ȭ��ѱ涧 ���)
        Engine::Rendering::Pipeline::Effect::set_y((playing_time/ min_loading_time)* CAM_SIZE_H);
        _Image_manager->render_loading();

        //�ִϸ��̼����� �ε��� �׸���
        //_Anime->render_loading(Engine::Time::Get::Delta());
        if (playing_time > waiting_time)
        {
            dispose_objects();
            if (!_Turn->check_tank_falling(tank) and playing_time > min_loading_time)
            {
                _Anime->render_loading_end(Engine::Time::Get::Delta());
                if(_Anime->get_loading_time() < 0.1f and playing_time > min_loading_time+ 0.5f)
                {
                    Engine::Rendering::Pipeline::Effect::set_y(MAPSIZE_H+200); //UI�����ŭ ����
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


        _Turn->checkturn(tank,missile);	//��üũ�� ������ �ο�
        _Input_manager->input(tank,missile,Engine::Time::Get::Delta());

        dispose_objects();            //�̵���� �� �浹�˻�


        render_playing();            //������

       
        if (_Turn->is_gameover(tank))
        {
            _Button->scene_buttons.erase("exit");
            this->state = State::GameOver;
        }
        _Button->render_buttons();
        for (auto iter = _Button->scene_buttons.begin(); iter != _Button->scene_buttons.end(); ++iter)
        {
            if (iter->second.clicked())	//���¿� ���� �̺�Ʈ ó��
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

        //��ư�� ������ ����ȭ������
        _Button->render_buttons();
        for (auto iter = _Button->scene_buttons.begin(); iter != _Button->scene_buttons.end(); ++iter)
        {
            if (iter->second.clicked())	//���¿� ���� �̺�Ʈ ó��
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
    _Physics_manager->ballistics(tank,missile,Engine::Time::Get::Delta());//�̵����� ����, �ʹ� ����
    _Physics_manager->Collide_objects(tank,missile,_Map_manager->hmapdc);//����� �ڸ����� �浹 �� ���� ó��
}

void S_Battle::render_playing() //Update
{
    _CAM->update();
    Camera.Location = { _CAM->pos.x,_CAM->pos.y };
    Camera.Set();

    _Map_manager->render_map();

    _Anime->render(tank,missile);
    _Text_manager->render(tank);

    _Image_manager->render_ui(tank);

    _Map_manager->render_minimap(tank);   

    //_Debug_manager->set_delta(Engine::Time::Get::Delta());
    //_Debug_manager->rendering();

    //Ÿ���� �� �����ϰ� �ѹ��� �� �׸��� ���
}
