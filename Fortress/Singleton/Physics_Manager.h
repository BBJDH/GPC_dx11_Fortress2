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

//유도 미사일 알고리즘
//미사일 하나당 유도미사일 범위 점대 원 충돌 검사
// 검사에 필요한것 : 미사일 위치, 유도 인식 범위, 탱크 위치
//탄도학 이동 계산을 끄고  목적지(충돌된 탱크 좌표)입력과 유도이동계산 시작
