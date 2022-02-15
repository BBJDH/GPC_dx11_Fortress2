#include "stdafx.h"
#include "S_Lobby.h"

void S_Lobby::set_exit_button()
{
    exit_button = new Button(_Button->
        bind_function<Scene*>(Button_manager::Func::Main_Title));
    exit_button->init_image_location(exit_x, exit_y);
    exit_button->init_image_size(exit_w, exit_h);
    exit_button->deactivated_image.Name = "Image/Button/Lobby/exit";
    exit_button->activated_image.Name = "Image/Button/Lobby/exit";
    exit_button->collide_image.Name = "Image/Button/Lobby/exit_collide";
}

void S_Lobby::set_start_button()
{
    start_button = new Button(_Button->
        bind_function<Scene*>(Button_manager::Func::Battle));
    start_button->init_image_location(start_x, start_y);
    start_button->init_image_size(start_w, start_h);
    start_button->deactivated_image.Name = "Image/Button/Lobby/start";
    start_button->activated_image.Name = "Image/Button/Lobby/start_active";
    start_button->collide_image.Name = "Image/Button/Lobby/start_collide";
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
    if (start_button->clicked())
        return start_button->execute();
    if (exit_button->clicked())
        return exit_button->execute();
    return nullptr;
}

void S_Lobby::End()
{
    delete exit_button;
    delete start_button;
}
