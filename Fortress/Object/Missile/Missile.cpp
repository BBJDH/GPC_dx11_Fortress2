#include"stdafx.h"

#include "Missile.h"

//Missile::Missile(_float2 const& pos, unsigned const width, unsigned const height,
//	Effect::Type const effect_type, Type const type, int const hit_limit):
//	Object(pos, width, height, 10), bomb_range{100,80},
//	damage{300}, ani_playtime{ 0.0f }, state{ State::In_Air }, type{ type },
//	hit_count{ 0 }, hit_limit{ hit_limit }, effect_type{ effect_type }
//{
//	animation.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
//	ani_set();
//}

Missile::Missile(_float2 const& pos, unsigned const width, unsigned const height,
	_float2 const& missile_range, int const damage, Effect::Type const effect_type,
	Hit_Type const hit_type, int const hit_limit)
	:Object(pos, width, height, 10), bomb_range{ missile_range },
	damage{ damage }, ani_playtime{ 0.0f }, state{ State::In_Air }, hit_type{ hit_type },
	hit_count{ 0 }, hit_limit{ hit_limit }, effect_type{ effect_type }
{
	animation.Length = Vector<2>(Missile_SIZE, Missile_SIZE);
	ani_set();
}

Missile::Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height, _float2 const& missile_range, int const damage, Effect::Type const effect_type, Angle_Type const angle_type, Hit_Type const hit_type, int const hit_limit)
	:Object(pos, width, height, 10), bomb_range{ missile_range }, name{ name },
	damage{ damage }, ani_playtime{ 0.0f }, state{ State::In_Air }, hit_type{ hit_type },
	hit_count{ 0 }, hit_limit{ hit_limit }, effect_type{ effect_type }, angle_type{ angle_type }
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
		boom(_Map_manager->hmapdc);  //¸ÊÆÄ±«
		_Physics_manager->collide_bomb(*this,_Tank->tanks);
		_Effect->push_effect(get_effect_type(), getpos());
		if (hit_count >= hit_limit)
		{
			state = State::Delete;
			//log
			//std::cout << "delete!" << std::endl;
		}
		else
		{
			state = State::In_Air;
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

void Missile::ballistics_equation(float const delta, float const wind)
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
	if(angle_type == Angle_Type::Angle)
		animation.Angle = -atan2(pos.y - previous.y, pos.x - previous.x) * 180 / PI;

	if (this->pos.y > MAPSIZE_H + OUT_RANGE or this->pos.x > MAPSIZE_W + OUT_RANGE or this->pos.x < 0 - OUT_RANGE - MAPSIZE_W)
	{
		this->out = true;
	}
}

void Missile::ani_set()
{
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}


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

Missile::Hit_Type Missile::get_type() const
{
	return hit_type;
}

Effect::Type Missile::get_effect_type() const
{
	return effect_type;
}

void Missile::boom(HDC const& hmapdc)
{

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
	std::string const location = "Animation/Missile/" + name;
	animation.Name = location.c_str();
	ani_playtime += delta;
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
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
