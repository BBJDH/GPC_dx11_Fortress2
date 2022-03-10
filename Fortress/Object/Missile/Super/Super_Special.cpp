#include "stdafx.h"
#include "Super_Special.h"

Super_Special::Super_Special(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, { 28,28 }, 90, Effect::Type::Super_Special), state{ State::Crusing },
	guide_target{ 0,0 }, guide_range{200}
{
	ani_set();
}
//가상 소멸자 오바라이딩이 제대로 되었는가
//오버라이딩된 렌더함수가 사용하는 함수들 모두 재정의가 필요한가
Super_Special::~Super_Special()
{
	int test=0;
}

void Super_Special::ani_render(float const delta)
{
	ani_playtime += delta;
	//check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	//this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

void Super_Special::ballistics_equation(float const delta, float const wind)
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
	animation.Angle = -atan2(pos.y- previous.y, pos.x - previous.x)*180/PI;

	if (this->pos.y > MAPSIZE_H + OUT_RANGE or this->pos.x > MAPSIZE_W + OUT_RANGE or this->pos.x < 0 - OUT_RANGE - MAPSIZE_W)
	{
		this->out = true;
	}
}


void Super_Special::check_guide_range()
{
	if (!_Tank->tanks.empty() and state == State::Crusing)
	{
		for (int i = 0; i < _Tank->tanks.size(); i++)
		{
			if(_Physics_manager->collide_guide_range(this, guide_range, _Tank->tanks[i]))
			{
				state = State::Guide;
				guide_target = _Tank->tanks[i]->getpos();
			}
		}
	}
}

void Super_Special::ani_set()
{
	animation.Name = "Animation/Missile/Super/special";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

//void Super_Special::ani_set_boom()
//{
//	animation.Name = "Animation/Effect/explosion4";
//	animation.Length = Vector<2>(350, 350);
//	animation.Duration = explosion_time;
//	animation.Repeatable = false;
//}
