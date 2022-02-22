#include "stdafx.h"
#include "Button_manager.h"


void Button_manager::init_slot_buttons()
{
	float const location_x = 270;
	float const location_y = 140;
	float const width = 190;
	float const heght = 42;

	float const offset = 44;

	for (int i = 0; i < 8; i++)
	{
		set_slot_button(slot_button,  "Lobby/slot",
			{ location_x, location_y + offset * i }, { width, heght });
	}
}

void Button_manager::init_tank_buttons()
{
	float const location_x = 70;
	float const location_y = 552;
	float const width = 90;
	float const heght = 60;
	float const offset_x = width + 8;
	float const offset_y = heght + 8;


	for (int i = 0; i < 12; i++)
	{
		if (i < 6)
		{
			set_slot_button(tank_button, "Lobby/tank",
				{ location_x + offset_x * i, location_y }, { width, heght });
		}
		else
		{
			set_slot_button(tank_button, "Lobby/tank",
				{ location_x + offset_x * (i - 6), location_y + offset_y }, { width, heght });
		}
	}
}

void Button_manager::update_map_button_text()
{
	if (!nomal_buttons.empty())
	{
		_float2 const location = map_button_set.find(map_name[map_index])->second.first;
		_float2 const length = map_button_set.find(map_name[map_index])->second.second;
		nomal_buttons.find("map")->second.set_name( "Lobby/Map/" +map_name[map_index]);
		nomal_buttons.find("map")->second.init_image_location(location);
		nomal_buttons.find("map")->second.init_image_size(length);
		_Map_manager->name = map_name[map_index];
	}
}

std::string Button_manager::get_map_name()
{
	return map_name[map_index];
}



void Button_manager::init_map_button_set()
{
	map_button_set.clear();
	map_button_set.insert
	(
		std::make_pair
		(
			"sky",
			std::make_pair
			(
				_float2{ 1100.0f,540.0f },
				_float2{ 45.0f,20.0f }
			)
		)
	);
	map_button_set.insert
	(
		std::make_pair
		(
			"friends",
			std::make_pair
			(
				_float2{ 1100.0f,540.0f },
				_float2{ 70.0f,20.0f }
			)
		)
	);
	map_button_set.insert
	(
		std::make_pair
		(
			"the artificial satellite",
			std::make_pair
			(
				_float2{ 1100.0f,540.0f },
				_float2{ 170.0f,20.0f }
			)
		)
	);
	map_button_set.insert
	(
		std::make_pair
		(
			"the valley of city",
			std::make_pair
			(
				_float2{ 1100.0f,540.0f },
				_float2{ 170.0f,20.0f }
			)
		)
	);
}

void Button_manager::check_buttons()
{
	for (auto iter = scene_buttons.begin(); iter != scene_buttons.end(); ++iter)
		iter->second.check_state();
	for (auto iter = nomal_buttons.begin(); iter != nomal_buttons.end(); ++iter)
		iter->second.check_state();
	for (auto iter = slot_button.begin(); iter != slot_button.end(); ++iter)
		iter->check_state();
	for (auto iter = tank_button.begin(); iter != tank_button.end(); ++iter)
		iter->check_state();
	update_map_button_text();
}

Button_manager::result Button_manager::slot_toggle(std::vector<Button<bool>>& slot)
{
	result result = {false,-1};
	int oldbutton_index = -1;
	if (!slot.empty())
	{
		for (int i = 0; i < slot.size(); ++i)
		{
			if (slot[i].get_on()) //��ư�� �����ִٸ�
			{
				oldbutton_index = i;
				result.index = i;
			}
		}
		for (int i = 0; i < slot.size(); ++i)
		{
			if (slot[i].clicked() and !slot[i].get_on())
			{//��ư�� ���� ���ȴٸ�
				result.clicked = true;
				slot[i].set_on(true);
				result.index = i;	//���� ��ư ������Ʈ
			}
		}
	}
	if(oldbutton_index !=-1  and result.clicked)	// ������ư�� �����ְ� ����ư ���ȴٸ�
		slot[oldbutton_index].set_on(false);

	return result;
}

void Button_manager::set_slot_button(std::vector<Button<bool>>& slot,
	std::string const& location, _float2 const & position, _float2 const& size)
{
	slot.push_back
	(
		{
			 Button<bool>(std::bind(&Button_manager::bool_func_default,_Button),location)
		}
	);
	slot.back().bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));
	slot.back().init_image_location(position);
	slot.back().init_image_size(size);
}

void Button_manager::update_player_set()
{
	//���� �Ǵ� ��ũ ��ư�� ���Ӱ� ���Ȱ� �ι�ư ��� ���� ������ �ִٸ� �̺�Ʈ �߻�
	//�ش� �����ε����� �ٰŷ� ���;ȿ� �����Ǿ��ִ��� Ȯ��
	//�����Ǿ��ִٸ�(�������� �ִٸ�)
	//��ũ��ư�� �ε��� �������ڿ��� ""�̶�� ���� ""�� �ƴ϶�� ������ �õ�
	// �����Ǿ����� �ʴٸ� (�������� �����ٸ�)
	// ������ �õ�

	//�̸��� "player"+tosting(���Թ�ư �ε��� +1)���� �ְ�
	//���õ� ��ũ��ư�� ��ũ�̸����� ��ȯ�Ͽ� �ְ�
	//���Թ�ư �ε����� �÷��� ĳ�����Ͽ� �ʿ� insert
	result slot_result = slot_toggle(slot_button);		//slot_0 ,,, ""
	result tank_result = slot_toggle(tank_button);		//��ư �������� �޾ƿ� canon, super, ""
	if((slot_result.clicked  or tank_result.clicked)
		and (slot_result.index!=-1 and tank_result.index != -1))
	{
		for (auto iter = player_set.begin(); iter < player_set.end(); iter++)
		{
			if ("slot_" + std::to_string(slot_result.index) == std::get<0>(*iter))//�����ϴ� ��ġ�ϴ� ������ �����Ѵٸ�
			{
				if (tank_name[tank_result.index] != "")	//����õ�
				{
					std::get<1>(*iter) = tank_name[tank_result.index];
				}
				else//����
				{
					player_set.erase(iter);
					//�÷��̾� ��ȣ ������
				}
				return;
			}
		}
		if (tank_name[tank_result.index] != "")
		{
			player_set.push_back
			(
				std::make_tuple
				(
					"slot_" + std::to_string(slot_result.index),
					tank_name[tank_result.index],
					static_cast<Color>(slot_result.index)
				)
			);
			//�÷��̾� ��ȣ ������
		}
		//player_set.emplace
		//(
		//	std::make_pair(slot_key, std::make_tuple("player "+std::to_string(slot_key+1), tank, static_cast<Color>(slot_key)))
		//);
	}

}

void Button_manager::init_start_button()
{
	float const start_x = 100;
	float const start_y = 690;
	float const start_w = 170;
	float const start_h = 30;
	scene_buttons.insert
	(
		{
			"start",
			 Button<Scene*>(std::bind(&Button_manager::to_battle,_Button),"Lobby/start")
		}
	);
	scene_buttons.at("start").bind_activated_func(std::bind(&Button_manager::check_ready, _Button));
	scene_buttons.at("start").init_image_location({ start_x, start_y });
	scene_buttons.at("start").init_image_size({ start_w, start_h });
}

void Button_manager::init_exit_button()
{
	float const exit_x = 1150;
	float const exit_y = 690;
	float const exit_w = 170;
	float const exit_h = 30;

	scene_buttons.insert
	(
		{
			"exit",
			 Button<Scene*>(std::bind(&Button_manager::quit,_Button),"Lobby/exit")
		}
	);
	scene_buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));

	scene_buttons.at("exit").init_image_location({ exit_x, exit_y });
	scene_buttons.at("exit").init_image_size({ exit_w, exit_h });

}

void Button_manager::render_tank_button_image()
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

void Button_manager::init_map_button()
{
	//float const exit_x = 1100;
	//float const exit_y = 540;
	//float const exit_w = 45;
	//float const exit_h = 20;

	nomal_buttons.insert
	(
		std::make_pair
		(
			"map",
			Button<bool>(std::bind(&Button_manager::switch_map,_Button),"Lobby/sky")
		)
	);
	nomal_buttons.find("map")->second.bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));
	update_map_button_text();
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

bool Button_manager::check_ready()
{
	return player_set.size()>=2;
}

bool Button_manager::switch_map()
{
	map_index++;
	if (map_index > map_name->size())
		map_index = 0;
	return true;
}
