#pragma once
#include "./Object/Tank/Tank.h"


class Missile_Tank : public Tank
{
public:
	Missile_Tank(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	~Missile_Tank()override;
	void ani_render(float const delta)override;
};