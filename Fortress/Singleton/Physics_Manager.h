#pragma once
#include"SingletonT.h"

class Physics_Manager : public SingletonT<Physics_Manager>
{
private:
public:
	unsigned const length(_float2 start, _float2 dest);
	bool Collide(HDC const hdc,int const x, int const y);
	float const calc_landing_angle(unsigned const start_x, unsigned const selected_y, HDC const& hmapdc);
	void Collide_objects(std::vector<Tank*>& tank,std::vector<Missile*>& missile, HDC const& hmapdc);
	bool Collide_object(Object & obj, HDC const& hmapdc);
	void collide_bomb(Missile const & missile,std::vector<Tank*>& tank);
	bool collide_button(Engine::Physics::Component<Quadrangle> const & button);
	//bool collide_missile_tank(Missile const & missile, Tank const & tank);
	bool collide_missile_tanks(Missile const * missile, std::vector<Tank*>& tank);
	void ballistics(std::vector<Tank*>& tank,std::vector<Missile*>& missile, std::vector<Patterns>& patterns, float const delta);
	bool collide_guide_range(Missile const* const missile,
		float const guide_range, Tank const* tank);
};

//���� �̻��� �˰���
//�̻��� �ϳ��� �����̻��� ���� ���� �� �浹 �˻�
// �˻翡 �ʿ��Ѱ� : �̻��� ��ġ, ���� �ν� ����, ��ũ ��ġ
//ź���� �̵� ����� ����  ������(�浹�� ��ũ ��ǥ)�Է°� �����̵���� ����
