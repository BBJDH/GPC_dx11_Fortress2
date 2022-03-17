#include "stdafx.h"
#include "Ion_Special.h"



Ion_Special::Ion_Special(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, { 66,50 }, 280, Effect::Type::Ion_Normal)
{
	ani_set();
}

Ion_Special::~Ion_Special()
{
}

void Ion_Special::ani_set()
{
	animation.Name = "Animation/Missile/Ion_Attacker/special";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}