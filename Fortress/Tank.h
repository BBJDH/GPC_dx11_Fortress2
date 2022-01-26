#pragma once
#include "Object.h"


class Tank : public Object
{
public:
	enum class State
	{
		Nomal, Idle, Idle2, Steady, Fire, Move, Stop, Fall, Dead, //...
	};
	enum class Side
	{
		Left, Right //...
	};

private:

	Engine::Rendering::Animation::Component animation;
	float ani_playtime;

	State		    state;
	Side		    side;
	unsigned	    hp;
	unsigned	    fuel;
	float const		fire_angle_min;
	float const		fire_angle_max;
	float		    fire_angle;
	float		    fire_velocity;

	void set_ani_flip();
	void set_ani_state();
	void set_ani_normal();
	void set_ani_idle();
	void set_ani_idle2();
	void set_ani_steady();
	void set_ani_fire();
	void set_ani_move();
	void set_ani_stop();
	void set_ani_fall();
	void set_ani_dead();

public:

	Tank(Position const& pos, unsigned const width, unsigned const height);
	Tank & operator=(Tank const & other_tank);
	unsigned const gethp() const;
	int const getpower()const;
	int const getfuel()const;
	int const getangle()const;
	int const getangle_min()const;
	int const getangle_max()const;
	bool is_dead()const;
	Tank::State get_state()const;
	Tank::Side get_side()const;
	void take_damage(unsigned const damage);
	void set_side(Side const side);
	void setstate(State const state);
	void plus_angle(int angle);
	void plus_power();
	void turn_setting();
	void stop_move(float const thetha);
	void ani_render(float const delta);
	void ani_start();


	
};


