#include "stdafx.h"
#include "Turnmanager.h"


Turnmanager::Turnmanager():rand(Random(0,PLAYERS-1,PLAYERS)),index{0},state{State::Tank_Turn}
{
}

unsigned const Turnmanager::whosturn()const
{
	return rand.GetResult(index);
}

Turnmanager::State Turnmanager::get_state()const
{
	return this->state;
}

void Turnmanager::is_gameover(std::vector<Tank>& tank)
{
	unsigned live_count =0;
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (!tank[i].is_dead())
			{
				live_count++;
			}
		}
		if(live_count<2)
			this->state = State::Over;
	}
}

bool Turnmanager::is_obj_turn(Object const& obj)
{
	return obj.is_myturn();
}

bool Turnmanager::is_tank_turn(std::vector<Tank>& tank)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (is_obj_turn(tank[i]) and !tank[i].is_dead())
			{
				_CAM->focusing(tank[i]);
				this->state = State::Tank_Turn;
				return true;
			}
		}
	}
	return false;
}

bool Turnmanager::check_tank_falling(std::vector<Tank>& tank)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (tank[i].is_falling())
			{
				_CAM->focus_on();

				_CAM->focusing(tank[i]);


				return true;
			}
		}
	}
	return false;
}

bool Turnmanager::is_missile_turn(std::vector<Missile>& missile)
{
	if (!missile.empty())
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			if (is_obj_turn(missile[i]))
			{
				_CAM->focus_on();

				_CAM->focusing(missile.back());
				//�̻����� �������ϼ� �����Ƿ� ������ �̻��ϸ� ����(����)
				this->state = State::Missile_Turn;

				return true;
			}
		}
	}
	return false;
}

void Turnmanager::checkturn(std::vector<Tank>& tank, std::vector<Missile>& missile)
{
	//������ ���� �������̸鼭 ����ְų�, �̻����� ���ư��� �ְų�, ���� ���������ִٸ� ��ŵ
	//�ش� ���� �޾Ҵµ� �׾��ٸ� ���������� �ѱ��
	if (check_tank_falling(tank) or is_tank_turn(tank) or is_missile_turn(missile))
	{	
		return ;
	}

	index++;		
	if(index>=PLAYERS)
		rerand();
	tankturn_start(tank);
}

void Turnmanager::tankturn_start(std::vector<Tank>& tank)
{
	tank[whosturn()].setmyturn(true);
	_CAM->focus_on();
	tank[whosturn()].turn_setting();
}


void Turnmanager::rerand()
{
    rand = Random(0,PLAYERS-1,PLAYERS);
	index =0;
}
