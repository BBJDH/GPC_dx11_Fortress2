#include "stdafx.h"
#include "Ballistic_Missile.h"


Ballistic_Missile::Ballistic_Missile(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, { 45,40 }, 200, Effect::Type::Super_Normal, Missile::Hit_Type::Multiple_Hit, 3)
{
	ani_set();

}

Ballistic_Missile::~Ballistic_Missile()
{
}

void Ballistic_Missile::ani_set()
{
}


void Ballistic_Missile::ballistics_equation(float const delta, float const wind)
{
}
