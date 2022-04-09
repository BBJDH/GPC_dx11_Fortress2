#pragma once
#include"SingletonT.h"
class Effect_manager :public SingletonT<Effect_manager>
{
public:

public:
	std::vector<Effect*> effects;
public:
	Effect_manager();
	//ȿ���̸�, ��ġ, ȿ�� ������, �÷��� Ÿ��
	void push_effect(Effect::Type const type, _float2 const& position, float const size_mul = 1.0f);
	//void render();
	void del_effect(Effect const * effect);
	void clear();
	~Effect_manager();
};