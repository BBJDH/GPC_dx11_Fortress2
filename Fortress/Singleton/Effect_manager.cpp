#include "stdafx.h"
#include "Effect_manager.h"

Effect_manager::Effect_manager()
{
}

void Effect_manager::push_effect(Effect::Type const type, _float2 const& position, float const size_mul)
{
	float effect_size = 0;
	switch (type)
	{
		
	case Effect::Type::Normal_Big:
	{
		effect_size = 300 * size_mul;
		effects.push_back(new Effect("explosion", position, { effect_size,effect_size }, 0.7f));
		break;
	}
	case Effect::Type::Normal_Small:
	{
		effect_size = 150 * size_mul;

		effects.push_back(new Effect("explosion", position, { effect_size,effect_size }, 0.7f));
		break;
	}
	case Effect::Type::Explosion_Super:
	{
		effect_size = 300 * size_mul;

		effects.push_back(new Effect("explosion_super", position, { effect_size,effect_size }, 0.5f));
		break;
	}
	case Effect::Type::Explosion_Missile:
	{
		effect_size = 400 * size_mul;

		effects.push_back(new Effect("explosion_missile", position, { effect_size,effect_size }, 0.5f));
		break;
	}
	case Effect::Type::Missile_Special:
	{
		effect_size = 500 * size_mul;

		effects.push_back(new Effect("explosion_special_missile", position, { effect_size,effect_size }, 0.5f));
		break;
	}
	case Effect::Type::Ion_Normal:
	{
		effect_size = 300 * size_mul;

		effects.push_back(new Effect("explosion_ion", position, { effect_size,effect_size }, 0.5f));
		break;
	}
	case Effect::Type::Explosion_Secwind:
	{
		effect_size = 400 * size_mul;

		effects.push_back(new Effect("explosion_secwind", position, { effect_size,effect_size }, 0.5f));
		break;
	}
	case Effect::Type::Explosion_Laser:
	{
		effect_size = 400 * size_mul;

		effects.push_back(new Effect("explosion_laser", position, { effect_size,effect_size }, 0.5f));
		break;
	}
	case Effect::Type::Explosion_Special_Laser:
	{
		effect_size = 400 * size_mul;

		effects.push_back(new Effect("explosion_special_laser", position, { effect_size,effect_size }, 0.5f));
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
		effects.push_back(new Effect("satellite_active", position, { 150,150 }, 1.0f));
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
