#include "stdafx.h"
#include "S_Lobby.h"

void S_Lobby::set_exit_button()
{
    _Button->buttons.insert
    (
        { 
            "exit",
             Button<Scene*>(_Button->bind_function<Scene*>(Button_manager::Func::Main_Title))
        }
    );
    _Button->buttons.at("exit").init_image_location(exit_x, exit_y);
    _Button->buttons.at("exit").init_image_size(exit_w, exit_h);
    _Button->buttons.at("exit").deactivated_image.Name = "Image/Button/Lobby/exit";
    _Button->buttons.at("exit").activated_image.Name = "Image/Button/Lobby/exit";
    _Button->buttons.at("exit").collide_image.Name = "Image/Button/Lobby/exit_collide";
}

void S_Lobby::set_start_button()
{
    _Button->buttons.insert
    (
        {
            "start",
             Button<Scene*>(_Button->bind_function<Scene*>(Button_manager::Func::Battle))
        }
    );
    _Button->buttons.at("start").init_image_location(start_x, start_y);
    _Button->buttons.at("start").init_image_size(start_w, start_h);
    _Button->buttons.at("start").deactivated_image.Name = "Image/Button/Lobby/start";
    _Button->buttons.at("start").activated_image.Name = "Image/Button/Lobby/start_active";
    _Button->buttons.at("start").collide_image.Name = "Image/Button/Lobby/start_collide";
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
}

Scene* S_Lobby::Update()
{
    render();
    for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
    {
        if (iter->second.clicked())
            return iter->second.execute();
    }
    //if (_Button->buttons["start"].clicked())
    //    return start_button->execute();
    //if (exit_button->clicked())
    //    return exit_button->execute();
    return nullptr;
}

void S_Lobby::End()
{
    _Button->buttons.erase("exit");
    _Button->buttons.erase("start");
}
