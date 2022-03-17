#include "stdafx.h"
#include "Ion_Normal.h"


Ion_Normal::Ion_Normal(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, { 100,80 }, 200, Effect::Type::Ion_Normal)
{
}

Ion_Normal::~Ion_Normal()
{
}

void Ion_Normal::ani_set()
{
	animation.Name = "Animation/Missile/Ion_Attacker/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}