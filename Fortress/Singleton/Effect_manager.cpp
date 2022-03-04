#include "stdafx.h"
#include "Effect_manager.h"

Effect_manager::Effect_manager()
{
}

void Effect_manager::push_effect(Type const type, _float2 const& position)
{
	switch (type)
	{
	case Effect_manager::Type::Normal:
	{
		Effects.push_back(new Effect_Normal(position));
		break;
	}
	case Effect_manager::Type::Super_Normal:
	{
		Effects.push_back(new Effect_Normal(position));

		break;
	}
	case Effect_manager::Type::Super_Special:
	{
		Effects.push_back(new Effect_Normal(position));

		break;
	}
	default:
		break;
	}
	
}
