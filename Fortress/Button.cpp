#include "stdafx.h"
#include "Button.h"


#pragma region 템플릿 정의
template<typename T>
Button<T>::Button() :state(State::De_Activated), collide_box{ Point{0,0},Point{0,0} }
{
}

template<typename T>
Button<T>::Button(std::function<T(void)> const& function, std::string const& name) :
	state(State::Activated), collide_box{ Point{0,0},Point{0,0} },
	click_function{ function }, function_button_on{ nullptr }, name{ name },
	on{ false }, function_button_toggle{nullptr}
{
}
template Button<Scene*>::Button(std::function<Scene* (void)> const& function, std::string const& name);
template Button<bool>::Button(std::function<bool(void)> const& function, std::string const& name);


template<typename T>
void Button<T>::init_image_size(float const button_w, float const button_h)
{

	image.Length = { button_w ,button_h };
	collide_box.Length = { button_w ,button_h };
}
template void Button<bool>::init_image_size(float const button_w, float const button_h);
template void Button<Scene*>::init_image_size(float const button_w, float const button_h);




template<typename T>
void Button<T>::init_image_location(float const button_x, float const button_y)
{

	image.Location = { button_x ,button_y };
	collide_box.Center = { button_x ,button_y };
}
template void Button<bool>::init_image_location(float const button_x, float const button_y);
template void Button<Scene*>::init_image_location(float const button_x, float const button_y);



template<typename T>
void Button<T>::check_state()
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
	set_button_image();
}
template void Button<bool>::check_state();
template void Button<Scene*>::check_state();


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
void Button<T>::set_button_image()
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
template void Button<bool>::set_button_image();
template void Button<Scene*>::set_button_image();

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

