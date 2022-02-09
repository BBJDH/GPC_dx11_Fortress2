#include "stdafx.h"
#include "Text_manager.h"

void Text_manager::set_text(Engine::Rendering::Text::Component& text, POINT const& location,
	SIZE const& font_size, std::string const& str_value, Color color)
{
	switch (color)
	{
	case Text_manager::Color::Green:
	{
		text.Color.Red = 0;
		text.Color.Blue = 0;
		text.Color.Green = 255;
		break;
	}
	case Text_manager::Color::Red:
	{
		text.Color.Red = 255;
		text.Color.Blue = 0;
		text.Color.Green = 0;
		break;
	}
	default:
	{
		text.Color.Red = 255;
		text.Color.Blue = 255;
		text.Color.Green = 255;
		break;
	}
	}
	text.Text = str_value.c_str();
	text.Font.Size = font_size.cy;

	text.Length = { font_size.cx, font_size.cy };
	text.Location = {  location.x,   location.y };
	
	text.Render();
}

void Text_manager::render_tank_angle(Tank const& tank)
{

	int  img_angle = -static_cast<int>(tank.getimage_angle() / Radian);
	int  barrel_angle = tank.getangle();
	int  min_angle = tank.getangle_min();
	int  max_angle = tank.getangle_max();
	if (tank.get_side() == Tank::Side::Left)
	{
		img_angle += 180;
		barrel_angle *= -1;
		min_angle *= -1;
		max_angle *= -1;
	}
	set_text
	(
		Ui_angle,
		{ tilt_angle_text_location_x,angle_text_location_y },
		angle_text_size,
		std::to_string(img_angle),
		Color::Green
	);
	set_text
	(
		Ui_angle,
		{ launch_angle_text_location_x,angle_text_location_y },
		angle_text_size,
		std::to_string(img_angle + min_angle + barrel_angle),
		Color::Green
	);
}

void Text_manager::render(std::vector<Tank> const& tank)
{
	render_tank_angle(tank[_Turn->whosturn()]);
}

Text_manager::Text_manager()
{
	Ui_angle.Font.Name = "Kostar";
	Ui_angle.Font.Bold = false;
	Ui_angle.Font.Italic = false;
	Ui_angle.Font.Underlined = false;
	Ui_angle.Font.StructOut = false;
}
