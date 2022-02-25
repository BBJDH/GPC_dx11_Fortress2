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
//	//	"ㅁㅈㄷㄹ",
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
	case Color::Green:
	{
		text.Color.Red = 0;
		text.Color.Blue = 0;
		text.Color.Green = 255;
		break;
	}
	case Color::Red:
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
	SIZE const angle_text_size = { 30,15 };
	int const tilt_angle_text_location_x = 125;
	int const launch_angle_text_location_x = 185;
	int const angle_text_location_y = 667;

	int  img_angle = -static_cast<int>(tank.getimage_angle() / Radian);
	int  barrel_angle = tank.getangle();
	int  min_angle = tank.getangle_min();
	int  max_angle = tank.getangle_max();
	if (tank.get_side() == Tank::Side::Left)
		img_angle *= -1;

	set_text
	(
		text,
		{ tilt_angle_text_location_x,angle_text_location_y },
		angle_text_size,
		std::to_string(img_angle),
		Color::Green
	);
	set_text
	(
		text,
		{ launch_angle_text_location_x,angle_text_location_y },
		angle_text_size,
		std::to_string(img_angle + min_angle + barrel_angle),
		Color::Green
	);
}

void Text_manager::render_damage(Tank const& tank)
{
	if (!tank.get_damage().empty())
	{
		//render_tank_text(tank[i]);
		LONG const location_x = static_cast<long>(tank.getpos().x) - MAPSIZE_W / 2 - 30 /*+ static_cast<long>(5*sin(tank.get_ani_playtime() * 10))*/;
		LONG const location_y = MAPSIZE_H / 2 - static_cast<long>(tank.getpos().y) + 30 + static_cast<long>(30*sqrt(tank.get_damage_showtime()));
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
		static_cast<Text_manager::Font>(tank.get_color())
	);
}
void Text_manager::render_text_ui(POINT const& location, int const& font_size, std::string const& str_value, Font font)
{
	LONG location_x = location.x;		//텍스트 출력위치 누적
	std::string value;
	if (str_value.empty())
		value = "Empty";
	else
		value = str_value;
	for (int i = 0; i < str_value.size(); i++)
	{
		if (str_value.at(i) == ' ')
			location_x += font_size / 2;
		else
			location_x += font_size;
		render_single_text
		(
			ui_text_img,
			{ location_x, location.y },
			{ font_size ,font_size },
			str_value.at(i),
			font
		);
	}
}
void Text_manager::render_fps()
{
	float const delta = Engine::Time::Get::Delta();
	std::string const value = std::to_string(static_cast<int>(1 / delta));
	text.Font.Bold = true;
	POINT const pos = { 50,15 };
	SIZE const size = { 80,25 };
	set_text
	(
		text,
		pos ,
		size,
		value,
		Color::Red
	);
	text.Font.Bold = false;

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
void Text_manager::render_single_text(Engine::Rendering::Image::Component text_img,
	POINT const& location, SIZE const& font_size, char const& value, Font font)
{
	if (value == ' ')
		return;
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
	case Text_manager::Font::Blue:
	{
		temp = "Image/Text/Normal/Blue/";
		break;
	}
	case Text_manager::Font::Green:
	{
		temp = "Image/Text/Normal/Green/";
		break;
	}
	case Text_manager::Font::Purple:
	{
		temp = "Image/Text/Normal/Purple/";
		break;
	}
	case Text_manager::Font::Orange:
	{
		temp = "Image/Text/Normal/Orange/";
		break;
	}
	case Text_manager::Font::Yellow:
	{
		temp = "Image/Text/Normal/Yellow/";
		break;
	}
	case Text_manager::Font::Brown:
	{
		temp = "Image/Text/Normal/Brown/";
		break;
	}
	case Text_manager::Font::Pink:
	{
		temp = "Image/Text/Normal/Pink/";
		break;
	}
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
	LONG location_x = location.x;		//텍스트 출력위치 누적
	std::string value;
	if (str_value.empty())
		value = "Empty";
	else
		value = str_value;
	for (int i = 0; i < str_value.size(); i++)
	{
		if (str_value.at(i) == ' ')
			location_x += font_size / 2;
		else
			location_x += font_size;
		render_single_text
		(
			text_img,
			{ location_x, location.y },
			{ font_size ,font_size },
			str_value.at(i),
			font
		);
	}
}

Text_manager::Text_manager()
{
	text.Font.Name = "Kostar";
	text.Font.Bold = false;
	text.Font.Italic = false;
	text.Font.Underlined = false;
	text.Font.StructOut = false;
	//text
}

void Text_manager::render_single_text(Engine::Rendering::Image::UI ui_text_img,
	POINT const& location, SIZE const& font_size, char const& value, Font font)
{
	if (value == ' ')
		return;
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
	case Text_manager::Font::Blue:
	{
		temp = "Image/Text/Normal/Blue/";
		break;
	}
	case Text_manager::Font::Green:
	{
		temp = "Image/Text/Normal/Green/";
		break;
	}
	case Text_manager::Font::Purple:
	{
		temp = "Image/Text/Normal/Purple/";
		break;
	}
	case Text_manager::Font::Orange:
	{
		temp = "Image/Text/Normal/Orange/";
		break;
	}
	case Text_manager::Font::Yellow:
	{
		temp = "Image/Text/Normal/Yellow/";
		break;
	}
	case Text_manager::Font::Brown:
	{
		temp = "Image/Text/Normal/Brown/";
		break;
	}
	case Text_manager::Font::Pink:
	{
		temp = "Image/Text/Normal/Pink/";
		break;
	}
	}
	temp += value;
	ui_text_img.Name = temp.c_str();
	ui_text_img.Location = Vector<2>(location.x, location.y);
	ui_text_img.Length = Vector<2>(font_size.cx, font_size.cy);
	ui_text_img.Render();
}
