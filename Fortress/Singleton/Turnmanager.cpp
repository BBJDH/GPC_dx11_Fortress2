#include "stdafx.h"
#include "Turnmanager.h"


Turnmanager::Turnmanager() : 
index{ 0 }, state{ State::Tank_Turn },
players{ static_cast<unsigned>(_Button->player_set.size()) },
wind{0}
{
	rand_array = Random(0, players - 1, players);
	set_wind();
}

unsigned const Turnmanager::whosturn()const
{
	return rand_array.GetResult(index);
}

Turnmanager::State Turnmanager::get_state()const
{
	return this->state;
}

float Turnmanager::get_wind() const
{
	return wind;
}

bool Turnmanager::is_gameover(std::vector<Tank*>& tank)
{
	unsigned live_count =0;
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (!tank[i]->is_dead())
			{
				live_count++;
			}
		}
		if (live_count < 2)
		{
			this->state = State::Over;
			return true;
		}
	}
	return false;

}

bool Turnmanager::is_obj_turn(Object const& obj)
{
	return obj.is_myturn();
}

bool Turnmanager::is_tank_turn(std::vector<Tank*>& tank)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (is_obj_turn(*tank[i]) and !tank[i]->is_dead())
			{
				_CAM->focusing(*tank[i]);
				this->state = State::Tank_Turn;
				return true;
			}
		}
	}
	return false;
}

bool Turnmanager::check_tank_falling(std::vector<Tank*>& tank)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (tank[i]->get_state() == Tank::State::Fall)
			{
				_CAM->focus_on();

				_CAM->focusing(*tank[i]);


				return true;
			}
		}
	}
	

	return false;
}

bool Turnmanager::is_missile_turn(std::vector<Missile*>& missile)
{
	if (!missile.empty())
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			if (is_obj_turn(*(missile[i])))
			{
				_CAM->focus_on();

				_CAM->focusing(*(missile.back()));
				//�̻����� �������ϼ� �����Ƿ� ������ �̻��ϸ� ����(����)
				this->state = State::Missile_Turn;

				return true;
			}
		}
	}
	return false;
}

bool Turnmanager::is_effect_turn(std::vector<Effect*>& effects)
{
	if (!effects.empty())
	{
		for (size_t i = 0; i < effects.size(); i++)
		{
			if (is_obj_turn(*(effects[i])))
			{
				_CAM->focus_on();

				_CAM->focusing(*(effects.back()));
				//�̻����� �������ϼ� �����Ƿ� ������ �̻��ϸ� ����(����)
				this->state = State::Effect_turn;

				return true;
			}
		}
	}
	return false;
}

void Turnmanager::checkturn(std::vector<Tank*>& tank, std::vector<Missile*>& missile, std::vector<Effect*>& effects)
{
	//������ ���� �������̸鼭 ����ְų�, �̻����� ���ư��� �ְų�, ���� ���������ִٸ� ��ŵ
	//�ش� ���� �޾Ҵµ� �׾��ٸ� ���������� �ѱ��
	if (check_tank_falling(tank) 
		or is_tank_turn(tank) 
		or is_missile_turn(missile) 
		or is_effect_turn(effects))
	{	
		return ;
	}
	next_turn();

}

bool Turnmanager::next_turn()
{
	_Tank->tanks[whosturn()]->setmyturn(false);
	index++;
	set_wind();
	if (index >= players)
		rerand();
	tankturn_start(*_Tank->tanks[whosturn()]);

	return true;
}

void Turnmanager::set_wind()
{
	int mul = 1;
	int const max_delta = 5;
	if (rand() % 2)
		mul *= -1;
	wind +=  (rand()% max_delta)* mul;
	if(wind>18) wind = 18;
	if(wind<-18) wind = -18;

}

void Turnmanager::tankturn_start(Tank  & tank)
{
	tank.setmyturn(true);
	_CAM->focus_on();
	tank.turn_setting();
}


void Turnmanager::rerand()
{
	rand_array = Random(0, players -1, players);
	index =0;
}
