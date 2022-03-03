#include "stdafx.h"
#include "Effect.h"

Effect::Effect(std::string const& location, _float2 const& position,
	_float2 const& size, float const duration)
	: name{ location }
{
	animation.Location = { position.x, position.y};
	animation.Length = { size.width(), size.height() };
	animation.Duration = duration;
}

void Effect::render()
{
	std::string const location = "Animation/Effect/"+name;
	animation.Name = location.c_str();

	animation.Render();
}
//동적할당 및 재생 후 delete, missile에서 제거 신호를 받아 missile도 delete