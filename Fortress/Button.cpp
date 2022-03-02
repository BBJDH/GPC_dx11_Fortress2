#include "stdafx.h"
#include "Button.h"


#pragma region 템플릿 정의
template<typename T>
Button<T>::Button() :state(State::De_Activated), collide_box{ Point{0,0},Point{0,0} }
{
}

template<typename T>
Button<T>::Button(std::string const& name, std::function<T(void)> const& function) :
	state(State::Activated), collide_box{ Point{0,0},Point{0,0} },
	click_function{ function }, function_button_on{ nullptr }, name{ name },
	on{ false }
{
}
template Button<Scene*>::Button(std::string const& name, std::function<Scene*(void)> const& function);
template Button<bool>::Button(std::string const& name, std::function<bool(void)> const& function);

template<typename T>
Button<T>::Button(std::string const& name, std::function<T(void)> const& onclick,
	std::function<bool(void)> const& active, _float2 const& position, _float2 const& length) :
	state(State::Activated), collide_box{ Point{position.x,position.y},Point{length.x,length.y} },
	click_function{ onclick }, function_button_on{ active }, name{ name },
	on{ false }
{
	init_image_location(position);
	init_image_size(length);
}
template Button<Scene*>::Button(std::string const& name, std::function<Scene*(void)> const& onclick,
	std::function<bool(void)> const& active, _float2 const& position, _float2 const& length);
template Button<bool>::Button(std::string const& name, std::function<bool(void)> const& onclick,
	std::function<bool(void)> const& active, _float2 const& position, _float2 const& length);


template<typename T>
void Button<T>::set_name(std::string const& name)
{
	this->name = name;
}
template void Button<bool>::set_name(std::string const& name);
template void Button<Scene*>::set_name(std::string const& name);

template<typename T>
void Button<T>::init_image_size(_float2 const& size)
{

	image.Length = { size.x ,size.y };
	collide_box.Length = { size.x ,size.y };
}
template void Button<bool>::init_image_size(_float2 const& size);
template void Button<Scene*>::init_image_size(_float2 const& size);




template<typename T>
void Button<T>::init_image_location(_float2 const& postion)
{

	image.Location = { postion.x ,postion.y };
	collide_box.Center = { postion.x ,postion.y };
}
template void Button<bool>::init_image_location(_float2 const& postion);
template void Button<Scene*>::init_image_location(_float2 const& postion);



template<typename T>
void Button<T>::update_state_and_render()
{



	if (activated())
	{

		switch (state)
		{

		case Button<T>::State::Activated:
		{
			if (_Physics_manager->collide_button(collide_box))
				state = State::Collide;
			break;
		}
		case Button<T>::State::Collide:
		{

			if (!_Physics_manager->collide_button(collide_box))
				state = State::Activated;
			else if (Engine::Input::Get::Key::Up(VK_LBUTTON))
				state = State::Clicked_Up;
			break;
		}
		case Button<T>::State::Clicked_Up:
		{
			state = State::Activated;
			break;
		}

		}
	}
	render();
}
template void Button<bool>::update_state_and_render();
template void Button<Scene*>::update_state_and_render();


template<typename T>
void Button<T>::make_clicked()
{
	this->state = State::Clicked_Up;
}
template void Button<bool>::make_clicked();
template void Button<Scene*>::make_clicked();

template<typename T>
bool Button<T>::clicked()
{
	return this->state == State::Clicked_Up;

}
template bool Button<bool>::clicked();
template bool Button<Scene*>::clicked();

template<typename T>
bool Button<T>::get_on()
{
	return on;
}
template bool Button<bool>::get_on();
template bool Button<Scene*>::get_on();


template<typename T>
void Button<T>::render()
{
	std::string  location_name = "";
	if (this->on)
	{
		location_name = "Image/Button/" + name + "_toggled";  //토글 이미지
		image.Name = location_name.c_str();
		image.Render();

		return;
	}

	location_name = "Image/Button/" + name;  //일반 버튼 비활성화 상태 이미지
	image.Name = location_name.c_str();
	if (this->activated())
	{
		switch (state)
		{

		case Button<T>::State::Activated:
		{
			location_name = "Image/Button/" + name+ "_activated";  //일반버튼 활성화 상태 이미지
			image.Name = location_name.c_str();
			break;
		}
		case Button<T>::State::Collide:
		{
			location_name = "Image/Button/" + name + "_collide";  //일반버튼 마우스충돌 상태 이미지
			image.Name = location_name.c_str();
			break;
		}
		case Button<T>::State::Clicked_Up:
		{
			location_name = "Image/Button/" + name + "_toggled";  //일반버튼 눌린(또는토글) 상태 이미지
			image.Name = location_name.c_str();
			break;
		}

		}
	}
	image.Render();
}
template void Button<bool>::render();
template void Button<Scene*>::render();

template<typename T>
bool Button<T>::activated()
{
	if (function_button_on == nullptr)
	{
		return false;
	}
	if(function_button_on())
	{

		return true;
	}
	return false;

}
template bool Button<bool>::activated();
template bool Button<Scene*>::activated();


template<typename T>
T Button<T>::execute() const
{
	if (click_function == nullptr)
		return static_cast<T>(nullptr);
	return click_function();
}
template bool Button<bool>::execute()const;
template Scene* Button<Scene*>::execute()const;

template<typename T>
void Button<T>::set_on(bool value)
{
	this->on = value;
}
template void Button<bool>::set_on(bool on);
template void Button<Scene*>::set_on(bool on);



template<typename T>
void Button<T>::bind_click_func(std::function<T (void)> const& function)
{
	this->click_function = function;
}
template void Button<bool>::bind_click_func(std::function<bool(void)> const& function);
template void Button<Scene*>::bind_click_func(std::function<Scene* (void)> const& function);

//template<>
//void Button<Scene*>::bind_click_func(std::function<Scene*(void)> const & function)
//{
//	this->click_function = function;
//}

template<typename T>
void Button<T>::bind_activated_func(std::function<bool(void)> const& function)
{
	this->function_button_on = function;
}
template void Button<bool>::bind_activated_func(std::function<bool(void)> const& function);
template void Button<Scene*>::bind_activated_func(std::function<bool(void)> const& function);

//template<>
//void Button<Scene*>::bind_activated_func(std::function<bool(void)> const& function)
//{
//	this->function_button_on = function;
//}
//template<typename T>
//void Button<T>::bind_toggled_func(std::function<bool(void)> const& function)
//{
//	this->function_button_toggle = function;
//}
//template void Button<bool>::bind_toggled_func(std::function<bool(void)> const& function);
//template void Button<Scene*>::bind_toggled_func(std::function<bool(void)> const& function);

//template<>
//void Button<Scene*>::bind_toggled_func(std::function<bool(void)> const& function)
//{
//	this->function_button_toggle = function;
//}
#pragma endregion

