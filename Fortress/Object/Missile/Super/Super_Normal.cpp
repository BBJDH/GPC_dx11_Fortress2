#include "stdafx.h"
#include "Super_Normal.h"



Super_Normal::Super_Normal(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, {45,45},200, Effect::Type::Super_Normal, Missile::Type::Multiple_Hit,3)
{
	ani_set();
}

Super_Normal::~Super_Normal()
{
	int test = 0;
}

void Super_Normal::ani_render(float const delta)
{

	ani_playtime += delta;
	//check_state();
	animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	animation.Render();
}

void Super_Normal::ballistics_equation(float const delta, float const wind)
{
	_float2 const previous = { pos };
	if (falling)
	{
		velocity0.x += wind * delta;
		this->moving_time += delta * speed;
		this->pos.x = this->pos0.x + (velocity0.x) * moving_time;
		this->pos.y = this->pos0.y - velocity0.y * moving_time
			+ (grav_accerl * static_cast<float>(pow(moving_time, 2))) / 2;
	}
	animation.Angle = -atan2(pos.y - previous.y, pos.x - previous.x) * 180 / PI;

	if (this->pos.y > MAPSIZE_H + OUT_RANGE or this->pos.x > MAPSIZE_W + OUT_RANGE or this->pos.x < 0 - OUT_RANGE - MAPSIZE_W)
	{
		this->out = true;
	}
}
//TODO: 다단히트에따른 탱크충돌 추가, 다단히트 데미지 누적
void Super_Normal::check_state()
{
	switch (this->state)
	{
	case Missile::State::In_Air:
	{
		break;
	}

	case Missile::State::Collide:
	{
		if (hit_count >= hit_limit)
		{
			state = State::Delete;
			//log
			//std::cout << "delete!" << std::endl << std::endl;
			break;
		}
		state = State::In_Air;
		reduce();
		boom(_Map_manager->hmapdc);  //맵파괴
		_Physics_manager->collide_bomb(*this, _Tank->tanks);
		_Effect->push_effect(get_effect_type(), getpos());
		hit_count++;
		falling = true;
		break;
	}
	case Missile::State::Delete:
	{
		break;
	}

	}
}

void Super_Normal::ani_set()
{
	animation.Name = "Animation/Missile/Super/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

void Super_Normal::reduce()
{
	_float2 reduction = { 15, 15};
	if (hit_count == 0)
		reduction= {0,0};
	float const mul = static_cast<float>(hit_count);
	bomb_range = { bomb_range.width() - reduction.width() ,bomb_range.height() - reduction.height() };
	damage = static_cast<int>(damage* 0.6);
}

//void Super_Normal::ani_set_boom()
//{
//	animation.Name = "Animation/Effect/explosion3";
//	animation.Length = Vector<2>(Missile_Explosion_SIZE, Missile_Explosion_SIZE);
//	animation.Duration = explosion_time;
//	animation.Repeatable = false;
//}
