#pragma once
#include"SingletonT.h"
class Effect_manager :public SingletonT<Effect_manager>
{
public:

public:
	std::vector<Effect*> effects;
public:
	Effect_manager();
	//효과이름, 위치, 효과 사이즈, 플레이 타임
	void push_effect(Effect::Type const type, _float2 const& position, float const size_mul = 1.0f);
	//void render();
	void del_effect(Effect const * effect);
	void clear();
	~Effect_manager();
};