#pragma once
#include "./Object/Tank/Tank.h"


class Ion_Attacker : public Tank
{
public:
	Ion_Attacker(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	~Ion_Attacker()override;
	void ani_render(float const delta)override;

};