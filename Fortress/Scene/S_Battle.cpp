
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
        tank.push_back(Tank({ static_cast<float>(r.GetResult(i)),0 }, Tank_SIZE, Tank_SIZE , "player "+std::to_string(i+1)));
        tank.back().ballistics_initialize(0, 0, Tank::State::Fall);
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
        //����Ʈ ����Ʈ ��
        Engine::Rendering::Pipeline::Effect::set_y((playing_time/ min_loading_time)* CAM_SIZE_H);
        _Image_manager->render_loading();

        //�ִϸ��̼����� �ε��� �׸���
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

        _Turn->checkturn(tank,missile);	//��üũ�� ������ �ο�
        _Input_manager->input(tank,missile,Engine::Time::Get::Delta());

        dispose_objects();            //�̵���� �� �浹�˻�

        render_playing();            //������

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

        //��ư�� ������ ����ȭ������
        if(exit_button->clicked())
            return exit_button->execute();
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
    _Map_manager->render_map();

    _Anime->render(tank,missile);
    _Text_manager->render(tank);

    _Image_manager->render_ui(tank);

    _Map_manager->render_minimap(tank);   

    _Debug_manager->set_delta(Engine::Time::Get::Delta());
    _Debug_manager->rendering();

    //Ÿ���� �� �����ϰ� �ѹ��� �� �׸��� ���
}
