#include "stdafx.h"
#include "Satellite_Missile.h"


Satellite_Missile::Satellite_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height, _float2 const& missile_range, int const damage, Effect::Type const effect_type)
	:Missile(name, pos, width, height, missile_range, damage, effect_type, Missile::Angle_Type::Angle),
	satellite_state{ Satellite_State::Initialize }, target_point{ 0,0 }, animate_time{0}
{
}

Satellite_Missile::~Satellite_Missile()
{
}



void Satellite_Missile::check_state()
{
	switch (this->state)
	{
	case Missile::State::In_Air:
	{
		break;
	}

	case Missile::State::Collide:
	{	
		//���� �̵� �� Ion ����Ʈ ��ȯ�� ballistics_equation���� ����
		if (satellite_state == Satellite_State::Launch and animate_time > 1.0f)
		{

			hit_count++;
			boom(_Map_manager->hmapdc);  //���ı�
			_Physics_manager->collide_bomb(*this, _Tank->tanks);
			_Effect->push_effect(get_effect_type(), getpos());
			if (hit_count >= hit_limit)
			{
				state = Missile::State::Delete;
				//log
				std::cout << "delete!" << std::endl << std::endl;
			}
			else
			{
				state = Missile::State::In_Air;
				falling = true;
			}
		}
		break;
	}
	case Missile::State::Delete:
	{
		break;
	}

	}

}

void Satellite_Missile::ballistics_equation(float const delta, float const wind)
{
	if (this->state == Missile::State::Collide)
	{

		switch (satellite_state)
		{
		case Satellite_Missile::Satellite_State::Initialize:
		{
			//���� �浹 �� ���� ����
			target_point = this->pos;
			this->pos.y = 0;
			satellite_state = Satellite_State::Move;
			this->name = "Ion_Attacker/satellite_move";
			this->animation.Angle = 0.0f;
			break;
		}
		case Satellite_Missile::Satellite_State::Move:
		{
			//���� �̵�
			this->pos.y += 50 * delta;
			if (this->pos.y > 50.0f)
			{
				_Effect->push_effect(Effect::Type::Satellite_Active, getpos());
				this->name = "Ion_Attacker/trace";
				satellite_state = Satellite_State::Active;
			}
			break;
		}
		case Satellite_Missile::Satellite_State::Active:
		{
			//���� �̿�ĳ�� ��¡
			//������ pos�� ��ź��(target_point) ��� y���� ����

			animate_time += delta;
			if (animate_time > 0.25f)//��¡�Ϸ�
			{
				_float2 const satellite_pos = pos;
				_Physics_manager->Collide_object(*this, _Map_manager->hmapdc, static_cast<unsigned>(target_point.y));
				_float2 const effect_pos = { satellite_pos.x, ((pos.y - 88) / 2)+ 94};
				//this->pos = target_point;
				_Effect->push_effect(Effect::Type::Ion, effect_pos);
				satellite_state = Satellite_State::Launch;
				//�� ����Ʈ ����
			}


			break;
		}
		case Satellite_Missile::Satellite_State::Launch:
		{
			animate_time += delta;

			break;
		}
		}
		return;
	}

	_float2 const previous = { pos };
	if (falling)
	{
		velocity0.x += wind * delta;
		this->moving_time += delta * speed;
		this->pos.x = this->pos0.x + (velocity0.x) * moving_time;
		this->pos.y = this->pos0.y - velocity0.y * moving_time
			+ (grav_accerl * static_cast<float>(pow(moving_time, 2))) / 2;
	}
	if (angle_type == Angle_Type::Angle)
		animation.Angle = -atan2(pos.y - previous.y, pos.x - previous.x) * 180 / PI;

	if (this->pos.y > MAPSIZE_H + OUT_RANGE or this->pos.x > MAPSIZE_W + OUT_RANGE or this->pos.x < 0 - OUT_RANGE - MAPSIZE_W)
	{
		this->out = true;
	}
}