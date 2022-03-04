#include "stdafx.h"
#include "Effect.h"

Effect::Effect(std::string const& location, _float2 const& position,
	_float2 const& size, float const duration)
	:  state{State::Playing},playtime{0.0f}, name{ location }, Object(position, 0, 0)
{
	myturn = true;
	animation.Location = { pos.x - MAPSIZE_W / 2,MAPSIZE_H / 2 - pos.y };
	animation.Length = { size.width(), size.height() };
	animation.Duration = duration;
}

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

void Effect::render()
{
	std::string const location = "Animation/Effect/"+name;
	animation.Name = location.c_str();
	animation.Render();
}
Effect::State Effect::get_state()
{
	return state;
}
//동적할당 및 재생 후 delete, missile에서 제거 신호를 받아 missile도 delete