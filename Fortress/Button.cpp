#include "stdafx.h"
#include "Button.h"


//�̹������, ������, ��ġ


Button::Button(std::string const& name, std::string const& clicked_name, float const location_x, float const location_y, float const length_x, float const length_y)
	:state{ State::Normal }, collide_box{ Point{location_x,location_y},Point{length_x,length_y} }
{
	image.Name = name.c_str();
	image.Location = { location_x ,location_y};
	image.Length = {length_x,length_y};
	clicked_image.Name = clicked_name.c_str();
	clicked_image.Location = image.Location;
	clicked_image.Length = { length_x-10,length_y-10 };
}

void Button::check_state()
{
	if (this->state == State::Clicked and
		Engine::Input::Get::Key::Up(VK_LBUTTON) and
		_Physics_manager->collide_button(collide_box))
	{
		this->state = State::Clicked_Up;
		return;
	}
	else if(Engine::Input::Get::Key::Down(VK_LBUTTON) and
		_Physics_manager->collide_button(collide_box))
	{
		this->state = State::Clicked;
		return;
	}
	this->state = State::Normal;

}

void Button::render() 
{
	switch (this->state)
	{
	case Button::State::Normal:
	{
		image.Render();
		break;
	}
	case Button::State::Clicked:
	{
		clicked_image.Render();
		break;
	}
	case Button::State::Clicked_Up:
	{
		image.Render();
		break;
	}
	}
}

bool Button::clicked() const
{
	return this->state==State::Clicked and
		   Engine::Input::Get::Key::Up(VK_LBUTTON) and
		_Physics_manager->collide_button(collide_box);
}
