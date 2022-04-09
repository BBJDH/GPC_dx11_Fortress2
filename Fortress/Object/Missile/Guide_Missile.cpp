#include "stdafx.h"
#include "Guide_Missile.h"

Guide_Missile::Guide_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height,
	_float2 const& missile_range, int const damage, float const guide_range, float const guide_speed, Effect::Type const effect_type)
	:Missile(name,pos, width, height, missile_range, damage, effect_type, Missile::Angle_Type::Angle), state{ State::Crusing },
	guide_target{ 0,0 }, guide_range{ guide_range }, guide_speed{ guide_speed } // 200 1500
{
	ani_set();
}
//가상 소멸자 오바라이딩이 제대로 되었는가
//오버라이딩된 렌더함수가 사용하는 함수들 모두 재정의가 필요한가
Guide_Missile::~Guide_Missile()
{
	int test=0;
}

void Guide_Missile::ani_render(float const delta)
{
	ani_playtime += delta;
	//check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	//this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
	if (state == State::Guide)
	{
		lock_on.Location = { guide_target.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - guide_target.y };
		lock_on.Render();
	}
}

void Guide_Missile::ballistics_equation(float const delta, float const wind)
{
	_float2 const previous = { pos };
	switch (state)
	{
	case Guide_Missile::State::Crusing:
	{
		velocity0.x += wind * delta;
		this->moving_time += delta * speed;
		this->pos.x = this->pos0.x + (velocity0.x) * moving_time;
		this->pos.y = this->pos0.y - velocity0.y * moving_time
			+ (grav_accerl * static_cast<float>(pow(moving_time, 2))) / 2;

		if(previous.y <pos.y)
			state = State::Ready;

		break;
	}
	case Guide_Missile::State::Ready:
	{
		if(check_guide_range())
		{ 
			state = State::Guide;
			break;
		}
		velocity0.x += wind * delta;
		this->moving_time += delta * speed;
		this->pos.x = this->pos0.x + (velocity0.x) * moving_time;
		this->pos.y = this->pos0.y - velocity0.y * moving_time
			+ (grav_accerl * static_cast<float>(pow(moving_time, 2))) / 2;
		break;
	}
	case Guide_Missile::State::Guide:
	{
		float const guide_angle = -atan2(guide_target.y - pos.y, guide_target.x - pos.x);
		float const cos_val = guide_speed * cos(guide_angle) * delta ;
		float const sin_val = guide_speed * sin(guide_angle) * delta ;

		pos.x = pos.x + cos_val;
		pos.y = pos.y - sin_val;

		break;
	}
	default:
		break;
	}
	//if (falling)
	//{

	//}
	animation.Angle = -atan2(pos.y- previous.y, pos.x - previous.x)*180/PI;			//미사일 이미지각

	if (this->pos.y > MAPSIZE_H + OUT_RANGE or this->pos.x > MAPSIZE_W + OUT_RANGE or this->pos.x < 0 - OUT_RANGE - MAPSIZE_W)
	{
		this->out = true;
	}
}


bool Guide_Missile::check_guide_range()
{
	_float2 target_pos = { 0,0 };
	unsigned target_length = 0;
	if (!_Tank->tanks.empty() )
	{
		for (int i = 0; i < _Tank->tanks.size(); i++)
		{
			if(_Tank->tanks[i]->get_state()!=Tank::State::Dead 
				and  _Physics_manager->collide_guide_range(this, guide_range, _Tank->tanks[i]))
			{
				target_pos = _Tank->tanks[i]->getpos();
				unsigned const temp_length = _Physics_manager->length(this->pos, target_pos);
				if (target_length == 0 or temp_length < target_length)
				{
					target_length = temp_length;
					guide_target = target_pos;
				}
			}

		}
	}

	return target_length != 0;

}

void Guide_Missile::ani_set()
{
	animation.Name = "Animation/Missile/Super/special";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
	lock_on.Name = "Animation/Missile/lock_on";
	lock_on.Duration = 0.3f;
	lock_on.Repeatable = true;
	lock_on.Length = { 100,100 };

}

//void Super_Special::ani_set_boom()
//{
//	animation.Name = "Animation/Effect/explosion4";
//	animation.Length = Vector<2>(350, 350);
//	animation.Duration = explosion_time;
//	animation.Repeatable = false;
//}
