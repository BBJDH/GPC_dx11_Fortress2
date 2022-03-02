#include "stdafx.h"
#include "Super_Normal.h"



Super_Normal::Super_Normal(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, {100,80},350)
{
}

Super_Normal::~Super_Normal()
{
	int test = 0;
}

void Super_Normal::ani_render(float const delta)
{
	ani_playtime += delta;
	check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Render();
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

void Super_Normal::check_state()
{

	switch (this->state)
	{
	case Missile::State::Throw:
	{
		ani_set_throw();
		break;
	}
	case Missile::State::Boom:
	{
		if (ani_playtime > explosion_time)
		{
			set_state(State::Delete);
		}
		else
			ani_set_boom();
		break;
	}
	case Missile::State::Delete:
	{
		break;
	}

	}
}

void Super_Normal::ani_set_throw()
{
	animation.Name = "Animation/Missile/Super/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

void Super_Normal::ani_set_boom()
{
	animation.Name = "Animation/Missile/explosion3";
	animation.Length = Vector<2>(Missile_Explosion_SIZE, Missile_Explosion_SIZE);
	animation.Duration = explosion_time;
	animation.Repeatable = false;
}
