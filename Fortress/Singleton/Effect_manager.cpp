#include "stdafx.h"
#include "Effect_manager.h"

Effect_manager::Effect_manager()
{
}

void Effect_manager::push_effect(Effect::Type const type, _float2 const& position)
{
	switch (type)
	{
	case Effect::Type::Normal_Big:
	{
		//effects.push_back(new Effect_Normal(position, {300,300}));
		effects.push_back(new Effect("explosion", position, { 300,300 }, 0.7f));
		break;
	}
	case Effect::Type::Normal_Small:
	{
		//effects.push_back(new Effect_Normal(position, { 150,150 }));
		effects.push_back(new Effect("explosion", position, { 150,150 }, 0.7f));
		break;
	}
	case Effect::Type::Super_Normal:
	{
		//effects.push_back(new Effect_Super_Normal(position));
		effects.push_back(new Effect("explosion_super", position, { 300,300 }, 0.5f));
		break;
	}
	case Effect::Type::Super_Special:
	{
		//effects.push_back(new Effect_Super_Special(position));
		effects.push_back(new Effect("explosion_missile", position, { 350,350 }, 0.5f));

		break;
	}
	case Effect::Type::Ion_Normal:
	{
		effects.push_back(new Effect("explosion_ion", position, { 300,300 }, 0.5f));

		break;
	}
	case Effect::Type::Ion:
	{
		//위성pos(y는 100)와 타격점pos 가운데 점 폭은 10 고정
		float const length_height = (position.y-88)*2;
		effects.push_back(new Effect("ion", position, { 20,length_height }, 0.75f));

		break;
	}
	case Effect::Type::Satellite_Active:
	{
		effects.push_back(new Effect("satellite_active", position, { 150,150 }, 1.75f));
		break;
	}
	default:
		break;
	}
	
}


void Effect_manager::del_effect(Effect const* effect)
{
	delete effect;
	effect = nullptr;
}

void Effect_manager::clear()
{
	if (!effects.empty())
	{
		for (int i = 0; i < effects.size(); i++)
		{
			if (effects[i] != nullptr)
			{
				del_effect(effects[i]);
			}
		}
		effects.clear();
		std::vector<Effect*>().swap(effects);
	}
}

Effect_manager::~Effect_manager()
{
	clear();
}
