#include "stdafx.h"
#include "Satellite_Missile.h"


Satellite_Missile::Satellite_Missile(std::string const& name, _float2 const& pos, unsigned const width, unsigned const height, _float2 const& missile_range, int const damage, Effect::Type const effect_type)
	:Missile(name, pos, width, height, missile_range, damage, effect_type, Missile::Angle_Type::Angle), satellite_state{ State::Satellite }
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
	//TODO: ������ȯ�� ���⼭ ���� ������ �Լ����� �̵������ ���� ���/���� �ؾ���
	// �̵��ϴµ��� ���� �ִϸ��̼� ���, ���� �� ���� �۵� �ִϸ��̼� ������ 
	//�������� ����Ʈ�� ó��, ������ ������ ���� ����Ʈ ���� �� delete�� �Ѿ
	case Missile::State::Collide:
	{	
		switch (satellite_state)
		{
		case Satellite_Missile::State::Satellite:
		{
			break;
		}
		case Satellite_Missile::State::Ion:
			break;

		}
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
		break;
	}
	case Missile::State::Delete:
	{
		break;
	}

	}

}
