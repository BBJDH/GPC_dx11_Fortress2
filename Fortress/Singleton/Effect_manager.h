#pragma once
#include"SingletonT.h"
class Effect_manager :public SingletonT<Effect_manager>
{
public:
	enum class Type
	{
		Normal, Super_Normal, Super_Special,
	};
private:
	std::vector<Effect*> Effects;
public:
	Effect_manager();
	void push_effect(Type const type, _float2 const & position);
};