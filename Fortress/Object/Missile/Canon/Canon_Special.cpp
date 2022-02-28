#include "stdafx.h"
#include "Canon_Special.h"

Canon_Special::Canon_Special(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height)
{
}
//가상 소멸자 오바라이딩이 제대로 되었는가
//오버라이딩된 렌더함수가 사용하는 함수들 모두 재정의가 필요한가
Canon_Special::~Canon_Special()
{
	int test=0;
}

void Canon_Special::ani_render(float const delta)
{
	ani_playtime += delta;
	check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

void Canon_Special::check_state()
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

void Canon_Special::ani_set_throw()
{
	animation.Name = "Animation/Missile/Canon/special";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

void Canon_Special::ani_set_boom()
{
	animation.Name = "Animation/Missile/explosion2";
	animation.Length = Vector<2>(150, 150);
	animation.Duration = explosion_time;
	animation.Repeatable = false;
}
