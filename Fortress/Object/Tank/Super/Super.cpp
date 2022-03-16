#include "stdafx.h"
#include "Super.h"

Super::Super(_float2 const& pos, unsigned const width, unsigned const height,
	std::string const& player_name, std::string const& tank_name, Color const color)
	:Tank(pos, width, height, player_name, tank_name, Tank::Tank_Type::Super, color)
{
	//this->animation.Length = Vector<2>(60, 60);
	this->animation.Length = Vector<2>(Tank_ANI_SIZE, Tank_ANI_SIZE);

}

Super::~Super()
{
	int test = 0;
}

void Super::ani_render(float const delta)
{
	ani_playtime += delta;
	damage_showtime += delta;
	ani_set_flip();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	std::string location = "Animation/Tank/" + this->tank_name + "/";
	switch (state)
	{
	case Tank::State::Nomal:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Idle:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Idle2:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Steady:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Fire:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Move:
	{
		location = location + "move";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Stop:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Fall:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Hit:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Danger:
	{
		location = location + "normal";
		this->animation.Name = location.c_str();
		break;
	}
	case Tank::State::Dead:
	{
		location = location + "dead";
		this->animation.Name = location.c_str();
		break;
	}
	default:
		break;
	}
	this->animation.Render();
}


