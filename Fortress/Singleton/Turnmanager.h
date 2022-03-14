#pragma once
#include"SingletonT.h"
#include"Random.h"
class Turnmanager :public SingletonT<Turnmanager>
{
public:
	enum class State
	{
		Tank_Turn, Missile_Turn, Effect_turn, Event, Over,
	};
	//int 번 탱크, int등 
	std::map<int, int> player_record;
private:
	Random rand_array;
	State state;
	unsigned players;
	unsigned index;
	float	 wind;
	int		 dead_count;

	bool is_obj_turn(Object const & obj);
	bool is_tank_turn(std::vector<Tank*>& tank);
	bool is_missile_turn(std::vector<Missile*>& missile);
	bool is_effect_turn(std::vector<Effect*>& effects);
	void rerand();
	void set_wind();

public:
	//각 플레이어와 미사일의 턴이 꺼져있으면 
	//다음플레이어의 턴을 켜준다
	//미사일의 턴은 탱크 미사일 발사시 켜지고 터지면삭제
	Turnmanager();
	unsigned const whosturn()const;
	State get_state()const;
	float get_wind()const;
	bool next_turn();
	bool check_tank_falling(std::vector<Tank*>& tank);
	bool is_gameover(std::vector<Tank*>& tank);
	void tankturn_start(Tank & tank);
	void checkturn(std::vector<Tank*> & tank, std::vector<Missile*> & missile, std::vector<Effect*>& effects);

};
