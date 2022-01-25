#pragma once
#include"SingletonT.h"

class Physics_Manager : public SingletonT<Physics_Manager>
{
private:
public:

	bool Collide(HDC const hdc,int const x, int const y);
	float const calc_landing_angle(unsigned const start_x, unsigned const selected_y, HDC const& hmapdc);
	bool Collide_object(Object & obj, HDC const& hmapdc);
	void Collide_objects(std::vector<Tank>& tank,std::vector<Missile>& missile, HDC const& hmapdc);
	void ballistics(std::vector<Tank>& tank,std::vector<Missile>& missile,float const delta);
	void collide_bomb(Missile const & missile,std::vector<Tank>& tank);





};
