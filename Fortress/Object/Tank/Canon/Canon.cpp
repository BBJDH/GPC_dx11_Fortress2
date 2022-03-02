#include "stdafx.h"
#include "Canon.h"

Canon::Canon(_float2 const& pos, unsigned const width, unsigned const height,
	std::string const& player_name, std::string const& tank_name,
	Color const color):Tank(pos,width,height,player_name,tank_name,Tank::Tank_Type::Canon,color)
{
}

Canon::~Canon()
{
}
