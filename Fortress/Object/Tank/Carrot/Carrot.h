#pragma once
#include "./Object/Tank/Tank.h"


class Carrot : public Tank
{
public:
	Carrot(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	~Carrot()override;
	void ani_render(float const delta)override;
};