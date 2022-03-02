#pragma once
#include"SingletonT.h"
#include"Random.h"
class Turnmanager :public SingletonT<Turnmanager>
{
public:
	enum class State
	{
		Tank_Turn, Missile_Turn, Item_turn, Over,
	};
private:
	Random rand_array;
	State state;
	unsigned players;
	unsigned index;
	float	 wind;

	bool is_obj_turn(Object const & obj);
	bool is_tank_turn(std::vector<Tank*>& tank);
	bool is_missile_turn(std::vector<Missile*>& missile);
	void rerand();
	void set_wind();

public:
	//�� �÷��̾�� �̻����� ���� ���������� 
	//�����÷��̾��� ���� ���ش�
	//�̻����� ���� ��ũ �̻��� �߻�� ������ ���������
	Turnmanager();
	unsigned const whosturn()const;
	State get_state()const;
	float get_wind()const;
	bool next_turn();
	bool check_tank_falling(std::vector<Tank*>& tank);
	bool is_gameover(std::vector<Tank*>& tank);
	void tankturn_start(Tank & tank);
	void checkturn(std::vector<Tank*> & tank, std::vector<Missile*> & missile);

};
