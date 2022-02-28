#pragma once
#include "./Object/Object.h"


class Tank : public Object
{
public:
/*
��Ȳ�� (255 127 0)
����� (255 255 0)
�ʷϻ� (0    128 0)
�Ķ��� (0    0    255)
��ȫ�� (255 192 203)
����� (139 0    255)
*/
	//����ִٸ�
	//falling �÷��� false �϶�  �Է¹��� ������
	//nomal, idle, idle2, Danger
	// �Է¹�����
	//  steady, fire, stop, move
	//falling �÷��� true �϶�
	// �¾Ҵ��� �ƴ����� �������� ����
	//Fall, Hit,
	//
	//�׾��ٸ�
	// Dead


	enum class State
	{
		Nomal, Idle, Idle2, Steady, Fire, Move, Stop, Fall, Hit, Danger, Dead, //...
	};
	enum class Side
	{
		Left, Right //...
	};
	enum class Missile_Type
	{
		Normal, Special  //...
	};
	enum class Tank_Type
	{
		Canon, Super
	};
private:
	//��� ����
	int const NAME_LOCATION_X = -8;
	int const NAME_LOCATION_Y = 15;

private:

	Engine::Rendering::Animation::Component animation;
	//Engine::Rendering::Text::Component damage;


	State		    state;
	Side		    side;
	Color			color;
	Tank_Type		tank_type;
	Missile_Type	missile_type;
	std::string	const	player_name;
	std::string	const	tank_name;
	std::string		damage;				//���� ������ ���ڷ� ����
	unsigned	    hp;
	unsigned	    fuel;
	unsigned const	max_fuel;
	float const		fire_angle_min;
	float const		fire_angle_max;
	float		    fire_angle;
	float		    fire_angle_left_value;
	float		    fire_velocity;
	float			ani_playtime;
	float			damage_showtime;
	int			power_record;
	int			power_guide;

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

	Tank(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	Tank & operator=(Tank const & other_tank);
	Tank::State get_state()const;
	Tank::Side get_side()const;
	std::string get_name()const;
	std::string get_damage()const;

	Color get_color()const;
	Missile_Type get_missile_type()const;
	Tank::Tank_Type get_tank_type()const;
	float const get_ani_playtime()const;
	float const get_damage_showtime()const;
	unsigned const gethp() const;
	int const getpower()const;
	int const getfuel()const;
	int const get_maxfuel()const;
	int const get_left_angle()const;
	int const getangle()const;
	int const getangle_min()const;
	int const getangle_max()const;
	int const get_power_guide()const;
	int const get_power_record()const;
	bool is_dead()const;
	void set_side(Side const side);
	void setstate(State const state);
	void set_missile_type(Missile_Type const type);
	void set_tank_type(Tank_Type const type);
	void check_state();
	void take_damage(unsigned const damage);
	void set_power_guide(int const value);
	void set_power_record(int const value);
	void plus_angle(int angle);
	void plus_power();
	void minus_fuel();
	void turn_setting();
	void ani_render(float const delta);
	void ani_start();
	
};


