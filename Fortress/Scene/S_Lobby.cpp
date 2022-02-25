#include "stdafx.h"
#include "S_Lobby.h"



void S_Lobby::render_tank_selected()
{
    float const tank_button_location_x = 38;
    float const tank_button_location_y = 140;
    float const tank_button_width = 30;
    float const tank_button_heght = 30;
    float const tank_button_offset_y = tank_button_heght + 14;

    for (auto iter = _Button->player_set.begin(); iter != _Button->player_set.end(); ++iter)
    {
        for (int i = 0; i < 8; i++)
        {
            if ("slot_" + std::to_string(i) == std::get<0>(*iter)) //������ �ش罽���� �˻�
            {
                _Image_manager->render_tank_image
                (
                    std::get<1>(*iter),
                    {
                        tank_button_location_x ,
                        tank_button_location_y + tank_button_offset_y *i
                    },
                    { tank_button_width, tank_button_heght }
                );
            }
        }
    }
}

void S_Lobby::render_slot_color()
{
    float const tank_button_location_x = 135;
    float const tank_button_location_y = 140;
    float const tank_button_width = 35;
    float const tank_button_heght = 22;
    float const tank_button_offset_y = 44;
    for (int i =0; i < 8; ++i)
    {
        _Image_manager->render_color
        (
            static_cast<Color>(i),
            {
                tank_button_location_x ,
                tank_button_location_y + tank_button_offset_y * i
            },
            { tank_button_width, tank_button_heght }
        );
    }
}

void S_Lobby::render_slot_text()
{
    int const tank_button_location_x = 180;
    int const tank_button_location_y = 140;
    int const tank_button_width = 100;
    int const tank_button_heght = 22;
    int const tank_button_offset_y = 44;
    int player_num = 1;
    for (auto iter = _Button->player_set.begin(); iter != _Button->player_set.end(); ++iter,++player_num)
    {
        for (int i = 0; i < 8; ++i)
        {
            if(std::get<0>(*iter) == "slot_"+std::to_string(i)) //�ش� ������ �˻�
            _Text_manager->render_text_ui
            (
                { 
                    tank_button_location_x ,
                    tank_button_location_y + tank_button_offset_y * i
                },
                tank_button_heght,
                "player "+std::to_string(player_num),
                static_cast<Text_manager::Font>(std::get<2>(*iter))
            );
        }
    }
    
}


void S_Lobby::render_slot_base()
{
    float const tank_button_location_x = 88;
    float const tank_button_location_y = 140;
    float const tank_button_width = 153;
    float const tank_button_heght = 40;
    float const tank_button_offset_y = 44;
    for (int i = 0; i < 8; ++i)
    {
        _Image_manager->render_selected_slot
        (
            {
                tank_button_location_x ,
                tank_button_location_y + tank_button_offset_y * i
            },
            { tank_button_width, tank_button_heght }
        );
    }
}

void S_Lobby::render_button_images()
{
    _Button->render_tank_button_image(); //��ũ��ư ���� �׸� �̹���
    render_slot_base();         //���� ���̽� ���
    render_tank_selected();
    render_slot_color();
    render_slot_text();
}


void S_Lobby::render()
{
    _Anime->render_background({ 832,-576 }, { 220,205 }, Engine::Time::Get::Delta()); //�κ� �� ��� �׸���
    _Image_manager->render_lobby_back();
    _Button->render_lobby_buttons();
    render_button_images();
}


void S_Lobby::Start()
{
    _Button->player_set.clear();
    _Button->init_lobby_buttons();
}

Scene* S_Lobby::Update()
{
    render();

    return _Button->scene_button_on();

}

void S_Lobby::End()
{
    _Button->clear_buttons();

}
