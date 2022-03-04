#include "stdafx.h"
#include "Effect_Normal.h"

Effect_Normal::Effect_Normal(_float2 const& position, _float2 const &size) 
	:Effect("explosion", position, size, 0.7f)
{
}

Effect_Normal::~Effect_Normal()
{
}
