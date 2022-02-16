#include "stdafx.h"
#include "S_Lobby.h"

bool S_Lobby::check_start_button()
{
    return true;
}

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

void S_Lobby::set_slot_button(std::string const& button_name,
    float const start_x, float const start_y, float const start_w, float const start_h )
{
    _Button->slot_button.insert
    (
        {
             button_name,
             Button<bool>(std::bind(&Button_manager::bool_func_default,_Button),"Lobby/slot")
        }
    );
    _Button->slot_button.at(button_name).bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));
    _Button->slot_button.at(button_name).init_image_location(start_x, start_y);
    _Button->slot_button.at(button_name).init_image_size(start_w, start_h);
    //_Button->buttons.at(button_name).deactivated_image.Name = "Image/Button/Lobby/slot";
    //_Button->buttons.at(button_name).activated_image.Name = "Image/Button/Lobby/slot_pressed";
    //_Button->buttons.at(button_name).collide_image.Name = "Image/Button/Lobby/slot";
    //_Button->buttons.at(button_name).bind_activated_func(std::bind());
    
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
        set_slot_button("slot_button_" + std::to_string(i),
            location_x , location_y + offset * i, width, heght);
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
}

Scene* S_Lobby::Update()
{
    render();

    _Button->check_buttons();
    for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
    {
        if (iter->second.clicked())
            return iter->second.execute();
    }
    _Button->slot_toggle();

    return nullptr;
}

void S_Lobby::End()
{
    _Button->buttons.erase("exit");
    _Button->buttons.erase("start");

    for (int i = 0; i < 8; ++i)
        _Button->slot_button.erase("slot_button_" + std::to_string(i));
}
