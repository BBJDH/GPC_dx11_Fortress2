#include "stdafx.h"
#include "Button_manager.h"


void Button_manager::init_player_set()
{
	for (int i = 0; i < 8; i++)
	{
		//player_set.insert(std::make_pair("player "+std::to_string(i+1), std::make_pair(tank_name[1], static_cast<Color>(i))));
		player_set.insert
		(
			std::make_pair(i, std::make_tuple("","", static_cast<Color>(i)))
		);
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

void Button_manager::update_player_set()
{
	//��ũ�� ���Թ�ư�� �����ִٸ�
	//Ű���� "player"+tosting(i+1)���� �ְ�
	//���õ� ��ũ��ư�� ��ũ�̸����� ��ȯ�Ͽ� �ְ�
	//�ش� ���Թ�ȣ�� �÷��� ĳ�����Ͽ� �ʿ� insert
	std::string slot = slot_toggle(slot_button);		//slot_0 ,,, ""
	std::string tank = slot_toggle(tank_button);		//��ư �������� �޾ƿ� canon, super, ""
	if(!slot.empty())
	{
		int slot_key = std::stoi(slot.substr(slot.find('_'),1));
		player_set.emplace
		(
			std::make_pair(slot_key, std::make_tuple("player "+std::to_string(slot_key+1), tank, static_cast<Color>(slot_key)))
		);
	}

}


void Button_manager::render_buttons()
{
	check_buttons();		//�� ��ư���� ���¸� ������Ʈ
	update_player_set();

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
std::string Button_manager::slot_toggle(std::map<std::string, Button < bool >> & slot)
{
	bool toggled = false;		//���� ��ư�� �־����� Ȯ��
	bool new_target = false;	//����ư�� ���ȴ��� Ȯ��
	auto oldbutton = slot.begin();
	auto newbutton = slot.begin();
	for (auto iter = slot.begin(); iter != slot.end(); ++iter)
	{
		if (iter->second.get_on()) //��ư�� �����ִٸ�
		{
			toggled = true;
			oldbutton = iter;
			newbutton = iter;
		}
		if (iter->second.clicked() and !iter->second.get_on())
		{//��ư�� ���� ���ȴٸ�
			new_target = true;
			iter->second.set_on(true);
			newbutton = iter;	//���� ��ư ������Ʈ
		}
	}
	if(toggled and new_target)	//����ư ���Ȱ� ������ư�� �����ִٸ�
		oldbutton->second.set_on(false);
	if(toggled)		//���ȴ� ��ư�� �ִٸ�
		return newbutton->first;
	return "";
}
