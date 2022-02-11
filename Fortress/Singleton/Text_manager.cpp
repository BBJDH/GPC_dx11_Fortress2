#include "stdafx.h"
#include "Text_manager.h"

//void Text_manager::render_tank_text(Tank const& tank)
//{
//	set_text
//	(
//		text,
//		{
//			static_cast<LONG>(tank.getpos().x - _CAM->pos_win.x + tank.getwidth() / 2 - 8),
//			static_cast<LONG>(tank.getpos().y - _CAM->pos_win.y + Tank_HP_Bar_Location_H + 15)
//		},
//		{ 100,15 },
//		tank.get_name(),
//		Color::Red
//	);
//
//	//set_text
//	//(
//	//	text,
//	//	{
//	//		100,
//	//		100
//	//	},
//	//	{ 100,15 },
//	//	"¤±¤¸¤§¤©",
//	//	Color::Red
//	//);
//
//	text.Render();
//}

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

void Text_manager::render_damage(Tank const& tank)
{
	if (tank.get_state() == Tank::State::Hit)
	{
		//render_tank_text(tank[i]);
		LONG const location_x = static_cast<long>(tank.getpos().x) - MAPSIZE_W / 2 - 30 /*+ static_cast<long>(5*sin(tank.get_ani_playtime() * 10))*/;
		LONG const location_y = MAPSIZE_H / 2 - static_cast<long>(tank.getpos().y) + 30 + static_cast<long>(30*sqrt(tank.get_ani_playtime()));
		//LONG const location_y = MAPSIZE_H / 2 - static_cast<long>(tank.getpos().y) + 30 + static_cast<long>(30*log10(tank.get_ani_playtime()*10+1));
		render_text
		(
			{ 
				location_x,location_y
			},
			//{100,100},
			15,
			tank.get_damage(),
			Font::Damage
		);
	}

}
void Text_manager::render_tank_name(Tank const& tank)
{
	LONG const location_x = static_cast<long>(tank.getpos().x) - MAPSIZE_W / 2 -50 /*+ static_cast<long>(5*sin(tank.get_ani_playtime() * 10))*/;
	LONG const location_y = MAPSIZE_H / 2 - static_cast<long>(tank.getpos().y) -45;
	render_text
	(
		{
			location_x,location_y
		},
		12,
		tank.get_name(),
		Font::Red
	);
}
void Text_manager::render(std::vector<Tank>& tank)
{
	if (!tank.empty())
	{
		for (int i = 0; i < tank.size(); i++)
		{
			if (i != _Turn->whosturn())
			{
				render_tank_name(tank[i]);
			}
			//
			render_tank_name(tank[_Turn->whosturn()]);
			render_damage(tank[i]);
		}
	}
}
void Text_manager::render_single_text(POINT const& location, SIZE const& font_size, char const & value, Font font)
{
	if (value == ' ')
	{
		//text_img.Name = "Image/Text/Normal/blank";
		//text_img.Location = Vector<2>(location.x, location.y);
		//text_img.Length = Vector<2>(font_size.cx/2, font_size.cy);
		//text_img.Render();
		return;
	}
	std::string temp = "";
	switch (font)
	{
	case Text_manager::Font::Damage:
	{
		temp = "Image/Text/Damage/";
		break;
	}
	case Text_manager::Font::Red:
	{
		temp = "Image/Text/Normal/Red/";
		break;
	}
	default:
		break;
	}
	temp += value;
	text_img.Name = temp.c_str();
	text_img.Location = Vector<2>(location.x, location.y);
	text_img.Length = Vector<2>(font_size.cx, font_size.cy);
	text_img.Render();
}
void Text_manager::render_text(POINT const& location, int const& font_size,
	std::string const& str_value, Font font)
{
	LONG location_x = location.x;
	for (int i = 0; i < str_value.size(); i++)
	{
		if (str_value.at(i) == ' ')
			location_x += font_size / 2;
		else
			location_x += font_size;
		render_single_text
		(
			{ location_x, location.y },
			{ font_size ,font_size },
			str_value.at(i),
			font
		);
	}
}



Text_manager::Text_manager()
{
	Ui_angle.Font.Name = "Kostar";
	Ui_angle.Font.Bold = false;
	Ui_angle.Font.Italic = false;
	Ui_angle.Font.Underlined = false;
	Ui_angle.Font.StructOut = false;

}
