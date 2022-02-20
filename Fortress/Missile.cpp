#include"stdafx.h"

#include "Missile.h"

Missile::Missile(_float2 const& pos, unsigned const width, unsigned const height):
	Object(pos, width, height),bomb_range_w(100),bomb_range_h(80),
	damage{500}, ani_playtime{ 0.0f }, state{ State::Throw }
{
	animation.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
}


void Missile::check_state()
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
		if (ani_playtime > ANI_Bomb_Boom)
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

void Missile::ani_set_throw()
{
	animation.Name = "Animation/Bomb/bomb";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

void Missile::ani_set_boom()
{
	animation.Name = "Animation/Bomb/explosion";
	animation.Length = Vector<2>(Missile_Explosion_SIZE, Missile_Explosion_SIZE);
	animation.Duration = ANI_Bomb_Boom;
	animation.Repeatable = false;
}


Missile& Missile::operator=(Missile const& other_miss)
{
	assign(other_miss);
	return *this;
}

int const Missile::get_range_w() const
{
	return bomb_range_w;
}

int const Missile::get_damage() const
{
	return damage;
}

Missile::State Missile::get_state() const
{
	return state;
}

void Missile::boom(HDC const& hmapdc)
{
	HBRUSH hNewBrush = CreateSolidBrush(RGB(255,0,255));
	HPEN hNewPen = CreatePen(PS_SOLID, 2, 0xff00ff);
	HBITMAP hOldBmp = static_cast<HBITMAP>(SelectObject(hmapdc, hNewBrush));
	SelectObject(hmapdc, hNewPen);
	int const x = static_cast<int const>(pos.x);
	int const y = static_cast<int const>(pos.y);
	Ellipse(hmapdc, x-bomb_range_w, y-bomb_range_h, x+bomb_range_w, y+bomb_range_h);
	SelectObject(hmapdc, hOldBmp);
	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
}

void Missile::ani_render(float const delta)
{
	ani_playtime += delta;
	check_state();
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
