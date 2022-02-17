#include "stdafx.h"
#include "Button_manager.h"


void Button_manager::init_player_set()
{
	for (int i = 0; i < 8; i++)
	{
		player_set.insert(std::make_pair(i, std::make_pair(tank_name[1], static_cast<Color>(i))));
	}
}

void Button_manager::check_buttons()
{
	for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
		iter->second.check_state();
	for (auto iter = _Button->slot_button.begin(); iter != _Button->slot_button.end(); ++iter)
		iter->second.check_state();
	for (auto iter = _Button->tank_button.begin(); iter != _Button->tank_button.end(); ++iter)
		iter->second.check_state();
}


void Button_manager::render_buttons()
{
	check_buttons();		//�� ��ư���� ���¸� ������Ʈ
	slot_toggle(slot_button); 	//���¿� ���� �̺�Ʈ ó��
	slot_toggle(tank_button); 	//���¿� ���� �̺�Ʈ ó��
}

Scene* Button_manager::quit()
{
	PostQuitMessage(0);
    return nullptr;
}
Scene* Button_manager::to_lobby()
{
	return  new S_Lobby;
}
Scene* Button_manager::to_battle()
{
	return new S_Battle;
}
bool Button_manager::bool_func_default()
{
	return true;
}
void Button_manager::slot_toggle(std::map<std::string, Button < bool >> & slot)
{
	bool toggled = false;
	bool new_target = false;
	auto onbutton = slot.begin();
	for (auto iter = slot.begin(); iter != slot.end(); ++iter)
	{
		if (iter->second.get_on())
		{
			toggled = true;
			onbutton = iter;
		}
		if (iter->second.clicked() and !iter->second.get_on())
		{
			new_target = true;
			iter->second.set_on(true);
		}
	}
	if(toggled and new_target)
		onbutton->second.set_on(false);
}
