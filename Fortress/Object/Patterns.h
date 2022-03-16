#pragma once
#include "Object.h"


class Patterns : public Object
{
private:
	Engine::Rendering::Animation::Component ani;
	std::string name;
	bool recyclable;
public:
	Patterns(std::string const & name, _float2 const& pos);
	void render();
	void recycle(); //오브젝트 재사용시 호출
	void set_recycle_able();  //오브젝트 수명이 다한 후 호출
	~Patterns()override;
};