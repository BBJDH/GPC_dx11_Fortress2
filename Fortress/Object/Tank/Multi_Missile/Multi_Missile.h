#pragma once
#include "./Object/Tank/Tank.h"


class Multi_Missile : public Tank
{
public:
	Multi_Missile(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	~Multi_Missile()override;
	void ani_render(float const delta)override;
};