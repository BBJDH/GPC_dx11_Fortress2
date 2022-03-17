#include "stdafx.h"
#include "Super_Special.h"

void Super_Special::ani_set()
{
	animation.Name = "Animation/Missile/Super/special";
	animation.Duration = ANI_Bomb_Throw;
	animation.Repeatable = true;
	lock_on.Name = "Animation/Missile/lock_on";
	lock_on.Duration = 0.3f;
	lock_on.Repeatable = true;
	lock_on.Length = { 100,100 };
}

Super_Special::Super_Special(_float2 const& pos, unsigned const width, unsigned const height):Guide_Missile("Super/special", pos, width, height,200,1500,Effect::Type::Super_Special)
{
}

Super_Special::~Super_Special()
{
}
