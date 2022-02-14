#include "stdafx.h"
#include "Button.h"


#pragma region ≈€«√∏¥ ¡§¿«
template<typename T>
Button<T>::Button() :state(State::De_Activated), collide_box{ Point{0,0},Point{0,0} }
{
}

template<typename T>
Button<T>::Button(std::function<T(void)> const& function) :
	state(State::Activated), collide_box{ Point{0,0},Point{0,0} },
	click_function{ function }, function_button_on{ nullptr }
{
}

//template<typename T>
//Button<T>::Button(std::string const& name, std::string const& clicked_name, float const location_x, float const location_y, float const length_x, float const length_y)
//	:state{ State::Normal }, collide_box{ Point{location_x,location_y},Point{length_x,length_y} }
//{
//	image.Name = name.c_str();
//	image.Location = { location_x ,location_y};
//	image.Length = {length_x,length_y};
//	collide_image.Name = clicked_name.c_str();
//	collide_image.Location = image.Location;
//	collide_image.Length = { length_x-10,length_y-10 };
//}

template Button<Scene*>::Button(std::function<Scene*(void)> const& function);

template<typename T>
void Button<T>::init_image_size(float const button_w, float const button_h)
{
	deactivated_image.Length = { button_w ,button_h };
	activated_image.Length = { button_w ,button_h };
	collide_image.Length = { button_w ,button_h };
	collide_box.Length = { button_w ,button_h };
}

template<typename T>
void Button<T>::init_image_location(float const button_x, float const button_y)
{
	deactivated_image.Location = { button_x ,button_y };
	activated_image.Location = { button_x ,button_y };
	collide_image.Location = { button_x ,button_y };
	collide_box.Center = { button_x ,button_y };
}

void Button<Scene*>::check_state()
{
	if (function_button_on == nullptr or activated())
	{
		switch (state)
		{
		case Button<Scene*>::State::Activated:
		{
			if (_Physics_manager->collide_button(collide_box))
			{
				state = State::Collide;
			}
			activated_image.Render();
			break;
		}
		case Button<Scene*>::State::Collide:
		{
			if (!_Physics_manager->collide_button(collide_box))
			{
				state = State::Activated;
			}
			else if (Engine::Input::Get::Key::Up(VK_LBUTTON))
			{
				state = State::Clicked_Up;
			}
			collide_image.Render();
			break;
		}
		case Button<Scene*>::State::Clicked_Up:
		{
			state = State::Collide;
			activated_image.Render();
			break;
		}
		}
	}
	else
		deactivated_image.Render();

}


bool Button<Scene*>::clicked()
{	
	check_state();
	return this->state == State::Clicked_Up;

}

template<typename T>
bool Button<T>::activated()
{
	return function_button_on();
}
Scene* Button<Scene*>::execute() const
{
	return click_function();
}
void Button<Scene*>::bind_click_func(std::function<Scene*(void)> const & function)
{
	this->click_function = function;
}

void Button<Scene*>::bind_activated_func(std::function<bool(void)> const& function)
{
	this->function_button_on = function;
}
#pragma endregion

