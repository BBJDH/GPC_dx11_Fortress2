#pragma once
#include "Object.h"


class Tank : public Object
{
public:
/*
주황색 (255 127 0)
노란색 (255 255 0)
초록색 (0    128 0)
파란색 (0    0    255)
분홍색 (255 192 203)
보라색 (139 0    255)
*/
	//살아있다면
	//falling 플래그 false 일때  입력받지 않을때
	//nomal, idle, idle2, Danger
	// 입력받을때
	//  steady, fire, stop, move
	//falling 플래그 true 일때
	// 맞았는지 아닌지는 데미지로 구분
	//Fall, Hit,
	//
	//죽었다면
	// Dead


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
	float			damage_showtime;

	void set_text_damage(unsigned const damage);
	void check_render_damage();
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

public:

	Tank(Position const& pos, unsigned const width, unsigned const height, std::string const & name);
	Tank & operator=(Tank const & other_tank);
	Tank::State get_state()const;
	Tank::Side get_side()const;
	std::string get_name()const;
	std::string get_damage()const;

	float const get_ani_playtime()const;
	float const get_damage_showtime()const;
	unsigned const gethp() const;
	int const getpower()const;
	int const getfuel()const;
	int const get_left_angle()const;
	int const getangle()const;
	int const getangle_min()const;
	int const getangle_max()const;
	bool is_dead()const;
	//void ballistics_initialize(float const moving_angle, float const velocity, State state);
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


