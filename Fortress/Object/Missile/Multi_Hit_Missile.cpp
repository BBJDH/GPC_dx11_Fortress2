#include "stdafx.h"
#include "Multi_Hit_Missile.h"



Multi_Hit_Missile::Multi_Hit_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height, _float2 const& missile_range, int const damage, int const hit_count, Effect::Type const effect_type)
	:Missile(name, pos, width, height, missile_range, damage, effect_type, Missile::Angle_Type::Angle, Missile::Hit_Type::Multiple_Hit, hit_count)
{
}

Multi_Hit_Missile::~Multi_Hit_Missile()
{
	int test = 0;
}



void Multi_Hit_Missile::check_state()
{
	switch (this->state)
	{
	case Missile::State::In_Air:
	{
		break;
	}

	case Missile::State::Collide:
	{
		
		hit_count++;
		boom(_Map_manager->hmapdc);  //¸ÊÆÄ±«
		_Physics_manager->collide_bomb(*this, _Tank->tanks);
		_Effect->push_effect(get_effect_type(), getpos());
		if (hit_count >= hit_limit)
		{
			state = State::Delete;
			//log
			//std::cout << "delete!" << std::endl << std::endl;
		}
		else
		{
			state = State::In_Air;
			reduce();
			falling = true;
		}
		break;
	}
	case Missile::State::Delete:
	{
		break;
	}

	}
}



void Multi_Hit_Missile::reduce()
{
	_float2 reduction = { 12, 10};
	if (hit_count == 0)
		reduction= {0,0};
	float const mul = static_cast<float>(hit_count);
	bomb_range = { bomb_range.width() - reduction.width() ,bomb_range.height() - reduction.height() };
	damage = static_cast<int>(damage* 0.6);
}
