#include "stdafx.h"
#include "Button_manager.h"

Scene* Button_manager::exit()
{
    return new S_Start;
}
template<typename T>
std::function<T(void)> Button_manager::bind_function(Func const state)
{
	switch (state)
	{
	case Button_manager::Func::Shop:
		return nullptr;
	case Button_manager::Func::Exit:
	{
		return std::bind(&Button_manager::exit,this);
	}
	default:
		return nullptr;
	}
}
template std::function<Scene*(void)> Button_manager::bind_function(Func const state);
