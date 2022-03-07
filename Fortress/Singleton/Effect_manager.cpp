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
		effects.push_back(new Effect_Normal(position, {300,300}));
		break;
	}
	case Effect::Type::Normal_Small:
	{
		effects.push_back(new Effect_Normal(position, { 150,150 }));
		break;
	}
	case Effect::Type::Super_Normal:
	{
		effects.push_back(new Effect_Super_Normal(position));

		break;
	}
	case Effect::Type::Super_Special:
	{
		effects.push_back(new Effect_Super_Special(position));

		break;
	}
	default:
		break;
	}
	
}

//void Effect_manager::render()
//{
//	if (!effects.empty())
//	{
//		for (int i = 0; i < effects.size(); ++i)
//		{
//			effects[i]->check_state();
//			if (effects[i]->get_state() == Effect::State::Delete)
//			{
//				delete  effects[i];
//				effects[i] = nullptr;
//				break;
//			}
//			effects[i]->render();
//		}
//		effects.clear();
//		std::vector<Effect*>().swap(effects);
//	}
//}

void Effect_manager::del_effect(Effect const* effect)
{
	delete effect;
	effect = nullptr;
}