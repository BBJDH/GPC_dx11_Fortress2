#include "stdafx.h"
#include "Button_manager.h"

Scene* Button_manager::to_main_title()
{
	PostQuitMessage(0);
    return new S_Start;
}
Scene* Button_manager::to_lobby()
{
	return  new S_Lobby;
}
Scene* Button_manager::to_battle()
{
	return new S_Battle;
}
template<typename T>
std::function<T(void)> Button_manager::bind_function(Func const state)
{
	switch (state)
	{
	case Button_manager::Func::Main_Title:
	{
		return std::bind(&Button_manager::to_main_title,this);
	}
	case Button_manager::Func::Shop:
		return nullptr;
	case Button_manager::Func::Lobby:
	{
		return std::bind(&Button_manager::to_lobby, this);
	}
	case Button_manager::Func::Battle:
	{
		return std::bind(&Button_manager::to_battle, this);
	}
	default:
		return nullptr;
	}
}
template std::function<Scene*(void)> Button_manager::bind_function(Func const state);
