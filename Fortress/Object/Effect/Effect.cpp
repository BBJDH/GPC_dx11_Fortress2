#include "stdafx.h"
#include "Effect.h"

void Effect::check_state()
{
	playtime += Engine::Time::Get::Delta();
	switch (state)
	{
	case Effect::State::Playing:
	{
		if (playtime > animation.Duration)
			state = State::Delete;
		break;
	}
	case Effect::State::Delete:
		break;

	}
}

Effect::Effect(std::string const& location, _float2 const& position,
	_float2 const& size, float const duration)
	: Object(position, 0, 0), name{ location }, state{State::Playing},
	playtime{0.0f}
{
	animation.Location = { pos.x, pos.y};
	animation.Length = { size.width(), size.height() };
	animation.Duration = duration;
}

void Effect::render()
{
	check_state();
	if (get_state() == State::Delete)
		return;

	std::string const location = "Animation/Effect/"+name;
	animation.Name = location.c_str();
	animation.Render();
}
Effect::State Effect::get_state()
{
	return state;
}
//동적할당 및 재생 후 delete, missile에서 제거 신호를 받아 missile도 delete