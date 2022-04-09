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
				{ location_x + offset_x * (i - 6), location_y + offset_y },
				{ width, heght });
		}
	}
}

void Button_manager::clear_buttons()
{
	scene_buttons.clear();
	nomal_buttons.clear();
	  slot_button.clear();
	  tank_button.clear();
}

void Button_manager::update_map_button_text()
{
	if (nomal_buttons.find("map") != nomal_buttons.end())
	{
		_float2 const location = map_button_set.find(map_name[map_index])->second.first;
		_float2 const length = map_button_set.find(map_name[map_index])->second.second;
		nomal_buttons.find("map")->second.set_name( "Lobby/Map/" +map_name[map_index]);
		nomal_buttons.find("map")->second.init_image_location(location);
		nomal_buttons.find("map")->second.init_image_size(length);
		_Map_manager->name = map_name[map_index];
	}
}

void Button_manager::init_lobby_buttons()
{
	init_map_button_set();
	init_start_button();
	init_exit_button();
	init_map_button();
	init_slot_buttons();
	init_tank_buttons();
}

void Button_manager::render_slot_base()
{
	_float2 const pos = {88, 140};
	_float2 const length = {153, 40};

	float const tank_button_offset_y = 44;
	for (int i = 0; i < 8; ++i)
	{
		_Image_manager->render_selected_slot
		(
			{
				pos.x ,
				pos.y + tank_button_offset_y * i
			},
			length
		);
	}
}

void Button_manager::render_tank_selected()
{
	_float2 const pos = {38,140};
	_float2 const length = {30,30};
	float const tank_button_offset_y = 44;

	for (auto iter = _Button->player_set.begin(); iter != _Button->player_set.end(); ++iter)
	{
		for (int i = 0; i < 8; i++)
		{
			if ("slot_" + std::to_string(i) == std::get<0>(*iter)) //벡터의 해당슬롯을 검색
			{
				_Image_manager->render_tank_icon
				(
					_Tank->tank_name[ static_cast<int>(std::get<1>(*iter))].c_str(),
					{
						pos.x ,
						pos.y + tank_button_offset_y * i
					},
					length
				);
			}
		}
	}
}

void Button_manager::render_missile_icon()
{
	_float2 const position = { 28 ,700 };
	_float2 const length = { 30 ,20 };

	float const offset = 240;

	_Image_manager->render_missile_icon
	(
		_Tank->tanks[_Turn->whosturn()]->get_tank_name(),
		"normal",
		{ position.x , position.y },
		length
	);

	_Image_manager->render_missile_icon
	(
		_Tank->tanks[_Turn->whosturn()]->get_tank_name(),
		"special",
		{ position.x +  offset , position.y },
		length
	);

}

void Button_manager::render_slot_color()
{
	_float2 pos = { 135,140 };
	_float2 length = { 35,22 };

	float const tank_button_offset_y = 44;

	for (int i = 0; i < 8; ++i)
	{
		_Image_manager->render_color
		(
			static_cast<Color>(i),
			{
				pos.x ,
				pos.y + tank_button_offset_y * i
			},
			length
		);
	}
}

void Button_manager::render_slot_text()
{
	POINT const pos = { 180, 140 };
	int const height = 22;
	int const tank_button_offset_y = 44;


	int player_num = 1;
	for (auto iter = _Button->player_set.begin(); iter != _Button->player_set.end(); ++iter, ++player_num)
	{
		for (int i = 0; i < 8; ++i)
		{
			if (std::get<0>(*iter) == "slot_" + std::to_string(i)) //해당 슬롯을 검색
				_Text_manager->render_text_ui
				(
					{
						pos.x ,
						pos.y + tank_button_offset_y * i
					},
					height,
					"player " + std::to_string(player_num),
					static_cast<Text_manager::Font>(std::get<2>(*iter))
				);
		}
	}
}

void Button_manager::render_lobby_button_images()
{
	render_tank_button_image(); //탱크버튼 위에 그릴 이미지
	render_slot_base();         //슬롯 베이스 출력
	render_tank_selected();
	render_slot_color();
	render_slot_text();
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

void Button_manager::render()
{
	for (auto iter = scene_buttons.begin(); iter != scene_buttons.end(); ++iter)
		iter->second.update_state_and_render();
	for (auto iter = nomal_buttons.begin(); iter != nomal_buttons.end(); ++iter)
	{
		iter->second.update_state_and_render();
		if (iter->second.clicked())	//상태에 따라 이벤트 처리
			iter->second.execute();
	}
	for (auto iter = slot_button.begin(); iter != slot_button.end(); ++iter)
		iter->update_state_and_render();
	for (auto iter = tank_button.begin(); iter != tank_button.end(); ++iter)
		iter->update_state_and_render();
}

Scene* Button_manager::scene_button_on()
{
	for (auto iter = scene_buttons.begin(); iter != scene_buttons.end(); ++iter)
	{
		if (iter->second.clicked())	//상태에 따라 이벤트 처리
		{
			return iter->second.execute();
		}
	}
	return nullptr;
}

Button_manager::result Button_manager::slot_toggle(std::vector<Button<bool>>& slot)
{
	result result = {false,-1};
	int oldbutton_index = -1;
	if (!slot.empty())
	{
		for (int i = 0; i < slot.size(); ++i)
		{
			if (slot[i].get_on()) //버튼이 눌려있다면
			{
				oldbutton_index = i;
				result.index = i;
			}
		}
		for (int i = 0; i < slot.size(); ++i)
		{
			if (slot[i].clicked() and !slot[i].get_on())
			{//버튼이 새로 눌렸다면
				result.clicked = true;
				slot[i].set_on(true);
				result.index = i;	//눌린 버튼 업데이트
			}
		}
	}
	if(oldbutton_index !=-1  and result.clicked)	// 이전버튼이 켜져있고 새버튼 눌렸다면
		slot[oldbutton_index].set_on(false);

	return result;
}

void Button_manager::set_slot_button(std::vector<Button<bool>>& slot,
	std::string const& location, _float2 const & position, _float2 const& size)
{
	slot.push_back
	(
		{
			 Button<bool>
			 (
				 location,
				 std::bind(&Button_manager::bool_func_default,_Button),
				 std::bind(&Button_manager::bool_func_default, _Button),
				 position,
				 size
			)
		}
	);
	//slot.back().bind_activated_func();
	//slot.back().init_image_location(position);
	//slot.back().init_image_size(size);
}

void Button_manager::update_player_set()
{
	//슬롯 또는 탱크 버튼이 새롭게 눌렸고 두버튼 모두 눌린 정보가 있다면 이벤트 발생
	//해당 슬롯인덱스를 근거로 벡터안에 생성되어있는지 확인
	//생성되어있다면(기존것이 있다면)
	//탱크버튼의 인덱스 참조문자열이 ""이라면 제거 ""이 아니라면 변경을 시도
	// 생성되어있지 않다면 (기존것이 없었다면)
	// 생성을 시도

	//이름은 "player"+tosting(슬롯버튼 인덱스 +1)으로 넣고
	//선택된 탱크버튼을 탱크이름으로 변환하여 넣고
	//슬롯버튼 인덱스를 컬러로 캐스팅하여 맵에 insert
	result slot_result = slot_toggle(slot_button);		//slot_0 ,,, ""
	result tank_result = slot_toggle(tank_button);		//버튼 눌린상태 받아옴 canon, super, ""
	if((slot_result.clicked  or tank_result.clicked)
		and (slot_result.index!=-1 and tank_result.index != -1))
	{
		for (auto iter = player_set.begin(); iter < player_set.end(); iter++)
		{
			if ("slot_" + std::to_string(slot_result.index) == std::get<0>(*iter))//벡터하는 일치하는 슬롯이 존재한다면
			{
				if (_Tank->tank_name[tank_result.index] != "")	//변경시도
				{
					std::get<1>(*iter) = static_cast<Tank::Tank_Type>(tank_result.index);
				}
				else//제거
				{
					player_set.erase(iter);
					//플레이어 번호 재정렬
				}
				return;
			}
		}
		if (_Tank->tank_name[tank_result.index] != "")
		{
			player_set.push_back
			(
				std::make_tuple
				(
					"slot_" + std::to_string(slot_result.index),
					static_cast<Tank::Tank_Type>(tank_result.index),
					static_cast<Color>(slot_result.index)
				)
			);
			//플레이어 번호 재정렬
		}
		//player_set.emplace
		//(
		//	std::make_pair(slot_key, std::make_tuple("player "+std::to_string(slot_key+1), tank, static_cast<Color>(slot_key)))
		//);
	}

}

void Button_manager::init_start_button()
{

	_float2 const& postion = {100,690};
	_float2 const& length = {170,30};
	scene_buttons.insert
	(
		{
			"start",
			 Button<Scene*>
			 (
				 "Lobby/start",
				 std::bind(&Button_manager::to_battle,this),
				 std::bind(&Button_manager::check_ready, this),
				 postion,
				 length
			 )
		}
	);
	//scene_buttons.at("start").bind_activated_func(std::bind(&Button_manager::check_ready, _Button));
	//scene_buttons.at("start").init_image_location({ start_x, start_y });
	//scene_buttons.at("start").init_image_size({ start_w, start_h });
}

void Button_manager::init_exit_button()
{

	_float2 const& postion = { 1150,690 };
	_float2 const& length = { 170,30 };

	scene_buttons.insert
	(
		{
			"exit",
			 Button<Scene*>
			 (
				 "Lobby/exit",
				 std::bind(&Button_manager::quit,this),
				 std::bind(&Button_manager::bool_func_default, this),
				 postion,
				 length
			 )
		}
	);
	//scene_buttons.at("exit").bind_activated_func(std::bind(&Button_manager::bool_func_default, _Button));

	//scene_buttons.at("exit").init_image_location({ exit_x, exit_y });
	//scene_buttons.at("exit").init_image_size({ exit_w, exit_h });

}

void Button_manager::render_tank_button_image()
{
	_float2 const pos = {70,552};
	_float2 const length = {80,50};
	_float2 const offset = { length.x +18,length.y+18};
	for (int i = 0; i < 12; i++)
	{
		if (i < 6)
		{
			_Image_manager->render_tank_icon
			(
				_Tank->tank_name[i],
				{
					pos.x + offset.x * i,
					pos.y
				},
				length
			);
		}
		else
		{
			_Image_manager->render_tank_icon
			(
				_Tank->tank_name[i],
				{
					pos.x + offset.x * (i-6),
					pos.y + offset.y
				},
				length
			);
		}
	}
}

void Button_manager::init_map_button()
{


	nomal_buttons.insert
	(
		std::make_pair
		(
			"map",
			Button<bool>("Lobby/sky", std::bind(&Button_manager::switch_map,this))
		)
	);
	nomal_buttons.find("map")->second.bind_activated_func(std::bind(&Button_manager::bool_func_default,this));
	update_map_button_text();
}


void Button_manager::render_lobby_buttons()
{
	render();		//각 버튼들의 상태를 업데이트
	update_map_button_text();
	update_player_set();
	render_lobby_button_images();
}

Scene* Button_manager::quit()
{
	PostQuitMessage(0);
    return nullptr;
}

void Button_manager::init_playing_exit_button()
{
	_float2 const pos = { 1200,705 };
	_float2 const length = { 130,18 };
	scene_buttons.insert
	(
		{
			"exit",
			 Button<Scene*>
			 (
				 "Battle/playing_exit",
				 std::bind(&Button_manager::to_lobby,this),
				 std::bind(&Button_manager::bool_func_default, this),
				 pos,
				 length
			 )
		}
	);
}

void Button_manager::init_skip_button()
{
	_float2 const pos = { 1199,599 };
    _float2 const length = { 150,18 };

    nomal_buttons.insert
    (
        {
            "skip",
             Button<bool>
             (
                 "Battle/skip",
                 std::bind(&Turnmanager::next_turn, _Turn),
				 std::bind(&Button_manager::bool_func_default, this),
				 pos,
				 length
             )
        }
    );
}

void Button_manager::init_power_arrow_button()
{
	_float2 const pos = { 770 ,669 };
	_float2 const length = { 655 ,35 };

	nomal_buttons.insert
	(
		{
			"guide",
			 Button<bool>
			 (
				 "Battle/guide",
				 std::bind(&Button_manager::set_power_guide,this),
				 std::bind(&Button_manager::bool_func_default, this),
				 pos,
				 length
			 )
		}
	);
}
void Button_manager::init_slot_missile_button()
{
	_float2 const location = { 28 ,700 };
	_float2 const length = { 50 ,35 };

	float const offset = 240;

	for (int i = 0; i < 2; i++)
	{
		set_slot_button(slot_button, "Battle/missile",
			{ location.x + offset * i , location.y }, { length.width(), length.height() });
	}
	slot_button.front().set_on(true);
}

void Button_manager::init_battle_buttons()
{
	init_playing_exit_button();
	init_skip_button();
	init_power_arrow_button();
	init_slot_missile_button();
}

void Button_manager::init_gameover_exit_button()
{
	_float2 const position = {1180,697} ;
	_float2 const length = {170,30} ;
	scene_buttons.insert
	(
		{
			"exit",
			 Button<Scene*>
			 (
				 "Battle/gameover_exit",
				 std::bind(&Button_manager::to_lobby,this),
				 std::bind(&Button_manager::bool_func_default, this),
				 position,
				 length
			 )
		}
	);
}

void Button_manager::render_battle_button()
{
	update_missile();
	render();
	render_missile_icon();
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

void Button_manager::update_missile()
{
	int const index = static_cast<int>(_Tank->tanks[_Turn->whosturn()]->get_missile_type());
	slot_button.at(index).make_clicked();
	result const selected_missile = slot_toggle(slot_button);
	Tank::Missile_Type selected = static_cast<Tank::Missile_Type>(selected_missile.index);
	_Tank->tanks[_Turn->whosturn()]->set_missile_type(selected);
}

bool Button_manager::set_power_guide()
{//x좌표 450~1090
	int const guide_power = static_cast<int const>((_Mouse->x - 450)/5);
	_Tank->tanks[_Turn->whosturn()]->set_power_guide(guide_power);
	return true;
}
