#include "stdafx.h"
#include "Button_manager.h"



void Button_manager::check_buttons()
{
	for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
		iter->second.check_state();
	for (auto iter = _Button->slot_button.begin(); iter != _Button->slot_button.end(); ++iter)
		iter->second.check_state();
	for (auto iter = _Button->tank_button.begin(); iter != _Button->tank_button.end(); ++iter)
		iter->second.check_state();
}

Scene* Button_manager::click_buttons()
{
	check_buttons();		//각 버튼들의 상태를 업데이트

	for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
	{
		if (iter->second.clicked())	//상태에 따라 이벤트 처리
			return iter->second.execute();
	}
	slot_toggle(slot_button); 	//상태에 따라 이벤트 처리
	slot_toggle(tank_button); 	//상태에 따라 이벤트 처리
	return nullptr;

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
