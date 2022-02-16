#include "stdafx.h"
#include "S_Lobby.h"



void S_Lobby::set_exit_button()
{
    _Button->buttons.insert
    (
        { 
            "exit",
             Button<Scene*>(std::bind(&Button_manager::quit,_Button),"Lobby/exit")
        }
    );
    _Button->buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));

    _Button->buttons.at("exit").init_image_location(exit_x, exit_y);
    _Button->buttons.at("exit").init_image_size(exit_w, exit_h);

}

void S_Lobby::set_start_button()
{
    _Button->buttons.insert
    (
        {
            "start",
             Button<Scene*>(std::bind(&Button_manager::to_battle,_Button),"Lobby/start")
        }
    );
    _Button->buttons.at("start").bind_activated_func(std::bind(&Button_manager::bool_func_default,_Button));

    _Button->buttons.at("start").init_image_location(start_x, start_y);
    _Button->buttons.at("start").init_image_size(start_w, start_h);

}

void S_Lobby::set_slot_button(std::map<std::string,Button<bool>>  & slot_button,
    std::string const& button_name, std::string const& location,
    float const start_x, float const start_y, float const start_w, float const start_h )
{
    slot_button.insert
    (
        {
             button_name,
             Button<bool>(std::bind(&Button_manager::bool_func_default,_Button),location)
        }
    );
    slot_button.at(button_name).bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));
    slot_button.at(button_name).init_image_location(start_x, start_y);
    slot_button.at(button_name).init_image_size(start_w, start_h);

    
}


void S_Lobby::set_slot_buttons()
{
    float const location_x = 270;
    float const location_y = 140;
    float const width = 190;
    float const heght = 42;

    float const offset = 44;

    for (int i = 0; i < 8; i++)
    {
        set_slot_button(_Button->slot_button,"slot_" + std::to_string(i), "Lobby/slot",
            location_x , location_y + offset * i, width, heght);
    }
}

void S_Lobby::set_tank_buttons()
{
    float const location_x = 70;
    float const location_y = 552;
    float const width = 90;
    float const heght = 60;
    float const offset_x = width+8;
    float const offset_y = heght +8;


    for (int i = 0; i < 12; i++)
    {
        if (i < 6)
        {
            set_slot_button(_Button->tank_button,"tank_" + std::to_string(i), "Lobby/tank",
                location_x + offset_x * i, location_y , width, heght);
        }
        else
        {
            set_slot_button(_Button->tank_button, "tank_" + std::to_string(i), "Lobby/tank",
                location_x + offset_x * (i-6), location_y+ offset_y, width, heght);
        }
    }
}


void S_Lobby::init_image()
{
    lobby.Name = "Image/Screen/lobby";
    lobby.Length = Vector<2>(CAM_SIZE_W, CAM_SIZE_H);
    lobby.Location = Vector<2>(CAM_SIZE_W / 2, CAM_SIZE_H / 2);
}

void S_Lobby::render()
{
    lobby.Render();
}


void S_Lobby::Start()
{
    init_image();
    set_exit_button();
    set_start_button();
    set_slot_buttons();
    set_tank_buttons();
}

Scene* S_Lobby::Update()
{
    render();

    return _Button->click_buttons();

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
