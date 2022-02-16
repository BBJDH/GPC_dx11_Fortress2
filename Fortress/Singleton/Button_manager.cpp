#include "stdafx.h"
#include "Button_manager.h"





void Button_manager::check_buttons()
{
	for (auto iter = _Button->buttons.begin(); iter != _Button->buttons.end(); ++iter)
		iter->second.check_state();
	for (auto iter = _Button->slot_button.begin(); iter != _Button->slot_button.end(); ++iter)
		iter->second.check_state();
}

Scene* Button_manager::quit()
{
	PostQuitMessage(0);
    return nullptr;
}
Scene* Button_manager::to_lobby()
{
	return  new S_Lobby;
}
Scene* Button_manager::to_battle()
{
	return new S_Battle;
}
bool Button_manager::bool_func_default()
{
	return true;
}
void Button_manager::slot_toggle()
{
	auto onbutton = slot_button.begin();
	for (auto iter = slot_button.begin(); iter != slot_button.end(); ++iter)
	{
		if (iter->second.get_on())
			onbutton = iter;
	}
	for (auto iter = slot_button.begin(); iter != slot_button.end(); ++iter)
	{
		if (iter->second.clicked() and !iter->second.get_on())
		{
			onbutton->second.set_on(false);
			iter->second.set_on(true);
		}
	}
}
//template<typename T>
//std::function<T(void)> Button_manager::bind_function(Scene_Func const scene_func)
//{
//	switch (scene_func)
//	{
//	case Button_manager::Scene_Func::Quit:
//	{
//		return std::bind(&Button_manager::to_main_title,this);
//	}
//	case Button_manager::Scene_Func::Shop:
//		return nullptr;
//	case Button_manager::Scene_Func::Lobby:
//	{
//		return std::bind(&Button_manager::to_lobby, this);
//	}
//	case Button_manager::Scene_Func::Battle:
//	{
//		return std::bind(&Button_manager::to_battle, this);
//	}
//	//case Button_manager::Scene_Func::Bool_default:
//	//{
//	//	return std::bind(&Button_manager::bool_func_default, this);
//	//	//return bind_function(&Button_manager::bool_func_default);
//	//}
//	default:
//		return nullptr;
//	}
//}
//template<typename T>
//std::function<bool(void)> Button_manager::bind_function()
//{
//	return std::function<bool(void)>();
//}
//template<typename T>
//std::function<T(void)> Button_manager::bind_function(std::function<T(void)> const func)
//{
//	return func;
//}
//template std::function<Scene*(void)> Button_manager::bind_function(Scene_Func const state);
//template std::function<bool(void)> Button_manager::bind_function(std::function<bool(void)> const func);
