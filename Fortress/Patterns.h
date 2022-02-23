#pragma once
#include "Object.h"


class Patterns : public Object
{
private:
	Engine::Rendering::Animation::Component ani;
	std::string name;
public:
	Patterns(std::string const & name, _float2 const& pos);
	void render();
};