#include "stdafx.h"
#include "Canon_Normal.h"



Canon_Normal::Canon_Normal(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, {100,80},350)
{
}

Canon_Normal::~Canon_Normal()
{
}

void Canon_Normal::ani_render(float const delta)
{
	ani_playtime += delta;
	check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

void Canon_Normal::check_state()
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

void Canon_Normal::ani_set_throw()
{
	animation.Name = "Animation/Missile/Canon/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

void Canon_Normal::ani_set_boom()
{
	animation.Name = "Animation/Effect/explosion";
	animation.Length = Vector<2>(Missile_Explosion_SIZE, Missile_Explosion_SIZE);
	animation.Duration = explosion_time;
	animation.Repeatable = false;
}
