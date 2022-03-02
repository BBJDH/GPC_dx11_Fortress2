#pragma once
#include "./Object/Tank/Tank.h"


class Canon : public Tank
{
public:
	Canon(_float2 const& pos, unsigned const width, unsigned const height,
		std::string const& player_name, std::string const& tank_name, Color const color);
	~Canon()override;
};