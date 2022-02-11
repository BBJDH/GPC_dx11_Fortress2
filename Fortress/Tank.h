#pragma once
#include "Object.h"


class Tank : public Object
{
public:
	enum class State
	{
		Nomal, Idle, Idle2, Steady, Fire, Move, Stop, Fall, Hit, Danger, Dead, //...
	};
	enum class Side
	{
		Left, Right //...
	};
private:
	//상수 세팅
	int const NAME_LOCATION_X = -8;
	int const NAME_LOCATION_Y = 15;

private:

	Engine::Rendering::Animation::Component animation;
	Engine::Rendering::Text::Component text;
	//Engine::Rendering::Text::Component damage;


	State		    state;
	Side		    side;
	std::string		name;
	std::string		damage;				//받은 데미지 기록
	unsigned	    hp;
	unsigned	    fuel;
	float const		fire_angle_min;
	float const		fire_angle_max;
	float		    fire_angle;
	float		    fire_angle_left_value;
	float		    fire_velocity;
	float			ani_playtime;

	void ani_set_flip();
	void ani_set_normal();
	void ani_set_idle();
	void ani_set_idle2();
	void ani_set_steady();
	void ani_set_fire();
	void ani_set_move();
	void ani_set_stop();
	void ani_set_fall();
	void ani_set_hit();
	void ani_set_danger();
	void ani_set_dead();
	void set_idle_state();
	void init_text();

public:

	Tank(Position const& pos, unsigned const width, unsigned const height, std::string const & name);
	Tank & operator=(Tank const & other_tank);
	Tank::State get_state()const;
	Tank::Side get_side()const;
	std::string get_name()const;
	std::string get_damage()const;

	float const get_ani_playtime()const;
	unsigned const gethp() const;
	int const getpower()const;
	int const getfuel()const;
	int const get_left_angle()const;
	int const getangle()const;
	int const getangle_min()const;
	int const getangle_max()const;
	bool is_dead()const;
	void ballistics_initialize(float const moving_angle, float const velocity, State state);
	void check_state();
	void take_damage(unsigned const damage);
	void set_side(Side const side);
	void setstate(State const state);
	void plus_angle(int angle);
	void plus_power();
	void minus_fuel();
	void turn_setting();
	void ani_render(float const delta);
	void ani_start();
	void text_render();
	

	
};


