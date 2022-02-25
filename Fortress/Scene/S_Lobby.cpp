#include "stdafx.h"
#include "S_Lobby.h"





void S_Lobby::render()
{
    _Anime->render_background({ 832,-576 }, { 220,205 }, Engine::Time::Get::Delta()); //�κ� �� ��� �׸���
    _Image_manager->render_lobby_back();
    _Button->render_lobby_buttons();
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
