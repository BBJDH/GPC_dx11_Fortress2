#include "stdafx.h"
#include "Effect_Normal.h"

Effect_Normal::Effect_Normal(_float2 const& position) :Effect("explosion", position, {300,300},0.7f)
{
}

Effect_Normal::~Effect_Normal()
{
}
