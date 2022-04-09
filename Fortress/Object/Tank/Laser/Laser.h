#pragma once
#include "./Object/Tank/Tank.h"


class Laser : public Tank
{
public:
	Laser(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	~Laser()override;
	void ani_render(float const delta)override;
};