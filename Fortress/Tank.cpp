#include"stdafx.h"
#include "Object.h"




Tank::Tank(Position const& pos, unsigned const width, unsigned const height)
	:Object(pos, width, height), hp{ TANK_HP }, fuel{100},
	fire_angle_min{35}, fire_angle_max{65},
	fire_angle{ 0 }, fire_velocity{ 0.0f }, state{ State::Nomal }, side{ Side::Left },
	ani_playtime{0.0f}
{
	set_ani_normal();
	this->animation.Length = Vector<2>(Tank_ANI_SIZE, Tank_ANI_SIZE);
}
Tank& Tank::operator=(Tank const& other_tank)
{
	assign(other_tank);
	this->state          = other_tank.state;
	this->hp             = other_tank.hp;
	this->fuel		     = other_tank.fuel;
	this->fire_angle     = other_tank.fire_angle;
	this->fire_velocity  = other_tank.fire_velocity;
	return *this;
}
//namespace Physics
//{
//	bool Collide(HDC const hdc, int const x, int const y)
//}
unsigned const Tank::gethp() const
{
	return this->hp;
}

int const Tank::getpower() const
{
	return static_cast<int const>(fire_velocity);
}

int const Tank::getfuel() const
{
	return this->fuel;
}

int const Tank::getangle() const
{
	return static_cast<int const>(fire_angle);
}

int const Tank::getangle_min() const
{
	return static_cast<int const>(fire_angle_min);
}

int const Tank::getangle_max() const
{
	return static_cast<int const>(fire_angle_max);
}

bool Tank::is_dead() const
{
	if (this->hp == 0)
	{
		return true;
	}
	return false;
}

void Tank::plus_power()
{
	fire_velocity++;
}

void Tank::turn_setting()
{
	this->fuel = 100;
	this->fire_velocity = 0;
}

void Tank::stop_move(float const thetha)
{
	setstate(State::Nomal);
	ani_playtime =0;
	Object::stop_move(thetha);
}

Tank::State Tank::get_state() const
{
	return state;
}

Tank::Side Tank::get_side() const
{
	return side;
}

void Tank::take_damage(unsigned const damage)
{
	if (damage >= this->hp)
	{
		this->hp =0;
		state = State::Dead;
		return;
	}
	this->hp -= damage;
}

void Tank::set_side(Side const side)
{
	this->side = side;
}

void Tank::setstate(State const state)
{
	ani_playtime =0.0f;
	this->state = state;
}

void Tank::plus_angle(int angle)
{
	this->fire_angle += angle;
	if(fire_angle >fire_angle_max-fire_angle_min or fire_angle<0)
		this->fire_angle -= angle;

}

void Tank::set_ani_flip()
{
	if (this->side == Tank::Side::Left)
		this->animation.Flipped = false;
	if (this->side == Tank::Side::Right)
		this->animation.Flipped = true;
}

void Tank::set_ani_state()
{
	switch (this->state)
	{
	case Tank::State::Nomal:
	{
		if (ani_playtime > ANI_Playtime_Nomal)
		{
			if (rand() % 2)
			{
				setstate(State::Idle);
				set_ani_idle();
				ani_start();
			}
			else
			{
				setstate(State::Idle2);
				set_ani_idle2();
				ani_start();
			}
		}
		else
			set_ani_normal();
		break;
	}
	case Tank::State::Idle:
	{
		if (ani_playtime > ANI_Playtime_Idle)
		{
			setstate(State::Nomal);
			set_ani_normal();
			ani_start();
		}
		else
			set_ani_idle();
		break;
	}
	case Tank::State::Idle2:
	{
		if (ani_playtime > ANI_Playtime_Idle2)
		{
			setstate(State::Nomal);
			set_ani_normal();
			ani_start();
		}
		else
			set_ani_idle2();
		break;
	}
	case Tank::State::Steady:
	{
		set_ani_steady();
		break;
	}
	case Tank::State::Fire:
	{
		if (ani_playtime > ANI_Playtime_Fire)
		{
			setstate(State::Nomal);
			set_ani_normal();
			ani_start();
		}
		else
			set_ani_fire();
		break;
	}
	case Tank::State::Move:
	{
		set_ani_move();
		break;
	}
	case Tank::State::Stop:
	{
		set_ani_stop();
		break;
	}
	case Tank::State::Fall:
	{
		set_ani_fall();
		break;
	}
	case Tank::State::Dead:
	{
		set_ani_dead();
		break;
	}
	default:
		break;
	}
}

void Tank::set_ani_normal()
{
	this->animation.Name = "Animation/Canon/nomal";
	this->animation.Duration = ANI_Playtime_Nomal;
	this->animation.Repeatable = true;
}

void Tank::set_ani_idle()
{
	this->animation.Name = "Animation/Canon/idle";
	this->animation.Duration = ANI_Playtime_Idle;
	this->animation.Repeatable = true;
}

void Tank::set_ani_steady()
{
	this->animation.Name = "Animation/Canon/steady";
	this->animation.Duration = ANI_Playtime_Fire;
	this->animation.Repeatable = true;
}

void Tank::set_ani_idle2()
{
	this->animation.Name = "Animation/Canon/idle2";
	this->animation.Duration = ANI_Playtime_Idle2;
	this->animation.Repeatable = true;
}

void Tank::set_ani_fire()
{
	this->animation.Name = "Animation/Canon/fire";
	this->animation.Duration = ANI_Playtime_Fire;
	this->animation.Repeatable = false;
}

void Tank::set_ani_move()
{
	this->animation.Name = "Animation/Canon/move";
	this->animation.Duration = ANI_Playtime_Move;
	this->animation.Repeatable = true;
}

void Tank::set_ani_stop()
{
	set_ani_normal();
}

void Tank::set_ani_fall()
{
	set_ani_move();
}

void Tank::set_ani_dead()
{
	this->animation.Name = "Animation/Canon/dead";
	this->animation.Duration = ANI_Playtime_Dead;
	this->animation.Repeatable = true;
}

void Tank::ani_render(float const delta)
{
	ani_playtime += delta;
	set_ani_state();
	set_ani_flip();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

void Tank::ani_start()
{
	this->animation.Playback =0;
}
