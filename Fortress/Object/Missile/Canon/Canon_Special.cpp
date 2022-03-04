#include "stdafx.h"
#include "Canon_Special.h"

Canon_Special::Canon_Special(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, {50,40}, 500, Effect::Type::Normal_Small)
{
	ani_set();
}
//���� �Ҹ��� ���ٶ��̵��� ����� �Ǿ��°�
//�������̵��� �����Լ��� ����ϴ� �Լ��� ��� �����ǰ� �ʿ��Ѱ�
Canon_Special::~Canon_Special()
{
}

void Canon_Special::ani_render(float const delta)
{
	ani_playtime += delta;
	//check_state();
	this->animation.Location = { this->pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - this->pos.y };
	this->animation.Angle = -this->image_angle / Radian;
	this->animation.Render();
}

//void Canon_Special::check_state()
//{
//	
//	switch (this->state)
//	{
//	case Missile::State::In_Air:
//	{
//		ani_set_throw();
//		break;
//	}
//
//	case Missile::State::Collide:
//	{
//		break;
//	}
//
//	}
//	
//}

void Canon_Special::ani_set()
{
	animation.Name = "Animation/Missile/Canon/special";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}

//void Canon_Special::ani_set_boom()
//{
//	animation.Name = "Animation/Effect/explosion";
//	animation.Length = Vector<2>(150, 150);
//	animation.Duration = explosion_time;
//	animation.Repeatable = false;
//}
