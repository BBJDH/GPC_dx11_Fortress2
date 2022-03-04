#include "stdafx.h"
#include "Effect_Super_Normal.h"

Effect_Super_Normal::Effect_Super_Normal(_float2 const& position) 
	:Effect("explosion_super_normal", position, { 300,300 }, 0.5f)
{
}

Effect_Super_Normal::~Effect_Super_Normal()
{
}
