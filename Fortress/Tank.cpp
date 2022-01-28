#include"stdafx.h"
#include "Object.h"




Tank::Tank(Position const& pos, unsigned const width, unsigned const height)
	:Object(pos, width, height), hp{ TANK_HP }, fuel{100},
	fire_angle_min{25}, fire_angle_max{55},//{25,55}
	fire_angle{ 0 }, fire_velocity{ 0.0f }, fire_angle_left_value{0.0f},
	state{ State::Nomal }, side{ Side::Right },
	ani_playtime{0.0f}
{
	ani_set_normal();
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

int const Tank::get_left_angle() const
{
	return static_cast<int>(this->fire_angle_left_value);
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
	if(fire_velocity<UI_POWER_MAX)
		fire_velocity++;
}

void Tank::turn_setting()
{
	this->fuel = 100;
	this->fire_velocity = 0;
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
		ani_start();
		return;
	}

	this->hp -= damage;
}

void Tank::set_side(Side const side)
{
	switch (side)
	{
	case Tank::Side::Left:
	{
		this->fire_angle_left_value = 180.0f;
		break;
	}
	case Tank::Side::Right:
	{
		this->fire_angle_left_value = 0.0f;
		break;
	}

	}
	this->side = side;
}

void Tank::setstate(State const state)
{
	ani_playtime =0.0f;
	this->state = state;
}

void Tank::set_idle_state()
{
	if (hp < TANK_DANGER_HP)
	{
		setstate(State::Danger);
		ani_set_danger();
		ani_start();
	}
	else
	{
		if (rand() % 2)
		{
			setstate(State::Idle);
			ani_set_idle();
			ani_start();
		}
		else
		{
			setstate(State::Idle2);
			ani_set_idle2();
			ani_start();
		}
	}
}

void Tank::plus_angle(int angle)
{
	this->fire_angle += angle;
	if(fire_angle >fire_angle_max-fire_angle_min or fire_angle<0)
		this->fire_angle -= angle;

}

void Tank::ani_set_flip()
{
	if (this->side == Tank::Side::Left)
		this->animation.Flipped = false;
	if (this->side == Tank::Side::Right)
		this->animation.Flipped = true;
}

void Tank::check_state()
{
	switch (this->state)
	{
	case Tank::State::Nomal:
	{
		if (ani_playtime > ANI_Tank_Nomal)
		{
			set_idle_state();
		}
		else
			ani_set_normal();
		break;
	}
	case Tank::State::Idle:
	{
		if (ani_playtime > ANI_Tank_Idle)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_idle();
		break;
	}
	case Tank::State::Idle2:
	{
		if (ani_playtime > ANI_Tank_Idle2)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_idle2();
		break;
	}
	case Tank::State::Steady:
	{
		ani_set_steady();
		break;
	}
	case Tank::State::Fire:
	{
		if (ani_playtime > ANI_Tank_Fire)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_fire();
		break;
	}
	case Tank::State::Move:
	{
		if (ani_playtime > ANI_Tank_Move)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_move();
		break;
	}
	case Tank::State::Stop:
	{
		if (ani_playtime > ANI_Tank_Stop)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_stop();
		break;
	}
	case Tank::State::Fall:
	{
		if (!falling and !hp==0)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_fall();
		break;
	}
	case Tank::State::Dead:
	{
		ani_set_dead();
		break;
	}
	case Tank::State::Danger:
	{
		if (ani_playtime > ANI_Tank_Danger)
		{
			setstate(State::Nomal);
			ani_set_normal();
			ani_start();
		}
		else
			ani_set_danger();
		break;
	}
	default:
		break;
	}
}

void Tank::ani_set_normal()
{
	this->animation.Name = "Animation/Canon/nomal";
	this->animation.Duration = ANI_Tank_Nomal;
	this->animation.Repeatable = true;
}

void Tank::ani_set_idle()
{
	this->animation.Name = "Animation/Canon/idle";
	this->animation.Duration = ANI_Tank_Idle;
	this->animation.Repeatable = true;
}

void Tank::ani_set_steady()
{
	this->animation.Name = "Animation/Canon/steady";
	this->animation.Duration = ANI_Tank_Fire;
	this->animation.Repeatable = true;
}

void Tank::ani_set_idle2()
{
	this->animation.Name = "Animation/Canon/idle2";
	this->animation.Duration = ANI_Tank_Idle2;
	this->animation.Repeatable = true;
}

void Tank::ani_set_fire()
{
	this->animation.Name = "Animation/Canon/fire";
	this->animation.Duration = ANI_Tank_Fire;
	this->animation.Repeatable = false;
}

void Tank::ani_set_move()
{
	this->animation.Name = "Animation/Canon/move";
	this->animation.Duration = ANI_Tank_Move;
	this->animation.Repeatable = true;
}

void Tank::ani_set_stop()
{
	this->animation.Name = "Animation/Canon/stop";
	this->animation.Duration = ANI_Tank_Stop;
	this->animation.Repeatable = true;
}

void Tank::ani_set_fall()
{
	this->animation.Name = "Animation/Canon/fall";
	this->animation.Duration = ANI_Tank_Fall;
	this->animation.Repeatable = true;
}

void Tank::ani_set_danger()
{
	this->animation.Name = "Animation/Canon/danger";
	this->animation.Duration = ANI_Tank_Danger;
	this->animation.Repeatable = false;
}

void Tank::ani_set_dead()
{
	this->animation.Name = "Animation/Canon/dead";
	this->animation.Duration = ANI_Tank_Dead;
	this->animation.Repeatable = true;
}

void Tank::ani_render(float const delta)
{
	ani_playtime += delta;
	check_state();
	ani_set_flip();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

void Tank::ani_start()
{
	this->animation.Playback =0;
}

void Tank::minus_fuel()
{
	if(this->fuel ==0);
	else
		this->fuel --;
}
