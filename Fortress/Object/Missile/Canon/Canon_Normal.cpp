#include "stdafx.h"
#include "Canon_Normal.h"



Canon_Normal::Canon_Normal(_float2 const& pos, unsigned const width, unsigned const height)
	:Missile(pos, width, height, {100,80},200,Effect::Type::Normal_Big)
{
	ani_set();
}

Canon_Normal::~Canon_Normal()
{
}

void Canon_Normal::ani_set()
{
	animation.Name = "Animation/Missile/Canon/normal";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
}
