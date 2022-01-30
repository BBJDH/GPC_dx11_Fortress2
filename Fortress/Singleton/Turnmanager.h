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
	Random rand;
	State state;
	unsigned index;

	bool is_obj_turn(Object const & obj);
	bool is_tank_turn(std::vector<Tank>& tank);
	bool is_missile_turn(std::vector<Missile>& missile);
	void rerand();

public:
	//각 플레이어와 미사일의 턴이 꺼져있으면 
	//다음플레이어의 턴을 켜준다
	//미사일의 턴은 탱크 미사일 발사시 켜지고 터지면삭제
	Turnmanager();
	unsigned const whosturn()const;
	State get_state()const;
	bool check_tank_falling(std::vector<Tank>& tank);
	bool is_gameover(std::vector<Tank>& tank);
	void tankturn_start(std::vector<Tank>& tank);
	void checkturn(std::vector<Tank> & tank, std::vector<Missile> & missile);


};
