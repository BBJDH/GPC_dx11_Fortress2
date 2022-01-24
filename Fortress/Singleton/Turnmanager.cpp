#include "stdafx.h"
#include "Turnmanager.h"

unsigned const Turnmanager::whosturn()
{
	return rand.GetResult(index);
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
			if(is_obj_turn(tank[i]) and !tank[i].is_dead())
				return true;
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
			if(tank[i].is_falling())
				return true;
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
			if(is_obj_turn(missile[i]))
				return true;
		}
	}
	return false;
}

void Turnmanager::checkturn(std::vector<Tank>& tank, std::vector<Missile>& missile)
{
	//������ ���� �������̸鼭 ����ְų�, �̻����� ���ư��� �ְų�, ���� ���������ִٸ� ��ŵ
	//�ش� ���� �޾Ҵµ� �׾��ٸ� ���������� �ѱ��
	int i =whosturn();
	if(is_tank_turn(tank) or is_missile_turn(missile) or check_tank_falling(tank))
		return ;
	index++;		

	if(index>=PLAYERS)
		rerand();
 	tank[whosturn()].setmyturn(true);
	tank[whosturn()].turn_setting();
}

void Turnmanager::rerand()
{
    rand = Random(0,PLAYERS-1,PLAYERS);
	index =0;
}

Turnmanager::Turnmanager():rand(Random(0,PLAYERS-1,PLAYERS)),index{0}
{
}

Turnmanager::~Turnmanager()
{
	rand.~Random();
}
