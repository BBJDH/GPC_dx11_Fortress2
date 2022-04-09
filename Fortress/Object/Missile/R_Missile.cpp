#include "stdafx.h"
#include "R_Missile.h"


R_Missile::R_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height,
	_float2 const& missile_range, int const damage, Effect::Type const effect_type)
	:Missile(name, pos, width, height, missile_range, damage, effect_type)
{
}

R_Missile::~R_Missile()
{
}

void R_Missile::ballistics_equation(float const delta, float const wind)
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
	if (angle_type == Angle_Type::Angle)
		animation.Angle = -atan2(pos.y - previous.y, pos.x - previous.x) * 180 / PI;

	if (this->pos.y > MAPSIZE_H + OUT_RANGE or this->pos.x > MAPSIZE_W + OUT_RANGE or this->pos.x < 0 - OUT_RANGE - MAPSIZE_W)
	{
		this->out = true;
	}
}

