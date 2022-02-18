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
            if ("slot_" + std::to_string(i) == std::get<0>(*iter)) //벡터의 해당슬롯을 검색
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
            if(std::get<0>(*iter) == "slot_"+std::to_string(i)) //해당 슬롯을 검색
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

void S_Lobby::render_tank_button_image()
{
    float const tank_button_location_x = 70;
    float const tank_button_location_y = 552;
    float const tank_button_width = 80;
    float const tank_button_heght = 50;
    float const tank_button_offset_x = tank_button_width + 18;
    float const tank_button_offset_y = tank_button_heght + 18;

    for (int i = 0; i < 12; i++)
    {
        if (i < 6)
        {
            _Image_manager->render_tank_image
            (
                _Button->tank_name[i],
                {
                    tank_button_location_x + tank_button_offset_x * i,
                    tank_button_location_y
                },
                { tank_button_width, tank_button_heght }
            );
        }
        else
        {
            _Image_manager->render_tank_image
            (
                _Button->tank_name[i],
                {
                    tank_button_location_x + tank_button_offset_x * i,
                    tank_button_location_y
                },
                { tank_button_width, tank_button_heght }
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
    render_tank_button_image(); //탱크버튼 위에 그릴 이미지
    render_slot_base();         //슬롯 베이스 출력
    render_tank_selected();
    render_slot_color();
    render_slot_text();
}


void S_Lobby::render()
{
    _Image_manager->render_lobby_back();
    _Button->render_buttons();
    render_button_images();
}


void S_Lobby::Start()
{
    _Button->player_set.clear();
    _Button->init_player_set();
    //init_image();
    _Button->set_exit_button();
    _Button->set_start_button();
    _Button->set_slot_buttons();
    _Button->set_tank_buttons();
}

Scene* S_Lobby::Update()
{
    render();

    for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
    {
        if (iter->second.clicked())	//상태에 따라 이벤트 처리
            return iter->second.execute();
    }

    return nullptr;

}

void S_Lobby::End()
{
    _Button->buttons.erase("exit");
    _Button->buttons.erase("start");

    _Button->slot_button.clear();
    _Button->tank_button.clear();
    //for (int i = 0; i < 8; ++i)
    //    _Button->slot_button.erase("slot_" + std::to_string(i));
    //for (int i = 0; i < 6; ++i)
    //    _Button->tank_button.erase("tank_" + std::to_string(i));
}
