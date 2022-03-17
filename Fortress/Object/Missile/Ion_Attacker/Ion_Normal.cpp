#include "stdafx.h"
#include "Ion_Normal.h"


Ion_Normal::Ion_Normal(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, { 48,40 }, 170, Effect::Type::Ion_Normal)
{
	ani_set();
}

Ion_Normal::~Ion_Normal()
{
}

void Ion_Normal::ballistics_equation(float const delta, float const wind)
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

void Ion_Normal::ani_set()
{
	animation.Name = "Animation/Missile/Ion_Attacker/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}