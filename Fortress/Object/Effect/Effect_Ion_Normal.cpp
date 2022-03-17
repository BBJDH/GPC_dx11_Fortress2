#include "stdafx.h"
#include "Effect_Ion_Normal.h"

Effect_Ion_Normal::Effect_Ion_Normal(_float2 const& position)
	:Effect("explosion_ion", position, { 300,300 }, 0.5f)
{
}

Effect_Ion_Normal::~Effect_Ion_Normal()
{
}
