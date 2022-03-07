#include"stdafx.h"

#include "Missile.h"

Missile::Missile(_float2 const& pos, unsigned const width, unsigned const height,
	Effect::Type const effect_type, Type const type, int const hit_limit):
	Object(pos, width, height, 10), bomb_range{100,80},
	damage{300}, ani_playtime{ 0.0f }, state{ State::In_Air }, type{ type },
	hit_count{ 0 }, hit_limit{ hit_limit }, effect_type{ effect_type }
{
	animation.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
	ani_set();
}

Missile::Missile(_float2 const& pos, unsigned const width, unsigned const height,
	_float2 const& range, int const dagame, Effect::Type const effect_type,
	Type const type, int const hit_limit)
	:Object(pos, width, height, 10), bomb_range{ range },
	damage{ dagame }, ani_playtime{ 0.0f }, state{ State::In_Air }, type{ type },
	hit_count{ 0 }, hit_limit{ hit_limit }, effect_type{ effect_type }
{
	animation.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
	ani_set();
}


void Missile::check_state()
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
		if (hit_count >= hit_limit)
		{
			state = State::Delete;
			break;
		}
		state = State::In_Air;
		falling = true;
		break;
	}
	case Missile::State::Delete:
	{
		break;
	}

	}
}

void Missile::ani_set()
{
	animation.Name = "Animation/Missile/Canon/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

//void Missile::ani_set_boom()
//{
//	animation.Name = "Animation/Missile/explosion";
//	animation.Length = Vector<2>(Missile_Explosion_SIZE, Missile_Explosion_SIZE);
//	animation.Duration = ANI_Bomb_Boom;
//	animation.Repeatable = false;
//}


Missile& Missile::operator=(Missile const& other_miss)
{
	assign(other_miss);
	return *this;
}

float const Missile::get_range_w() const
{
	return bomb_range.width();
}

int const Missile::get_damage() const
{
	return damage;
}

Missile::State Missile::get_state() const
{
	return state;
}

Missile::Type Missile::get_type() const
{
	return type;
}

Effect::Type Missile::get_effect_type() const
{
	return effect_type;
}

void Missile::boom(HDC const& hmapdc)
{
	if (hit_count == 0)
		bomb_range;

	HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
	HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
	HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
	SelectObject(hmapdc, hNewPen);
	int const x = static_cast<int const>(pos.x);
	int const y = static_cast<int const>(pos.y);
	int const range_w = static_cast<int const>(bomb_range.width());
	int const range_h = static_cast<int const>(bomb_range.height());
	Ellipse(hmapdc, x- range_w, y- range_h, x+ range_w, y+ range_h);
	SelectObject(hmapdc, hOldBmp);
	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
}

void Missile::ani_render(float const delta)
{
	ani_playtime += delta;
	//check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

void Missile::ani_start()
{
	this->ani_playtime =0.0f;
}

void Missile::set_state(State const state)
{
	this->state = state;
}
