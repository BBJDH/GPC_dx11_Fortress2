#include "stdafx.h"
#include "Physics.h"

bool Physics_Manager::Collide(HDC const hdc, int const x, int const y)
{
	//pipeline -> 스왑체인 텍스쳐2d를 gdi로 가져와서 getpixel

	COLORREF const color = GetPixel(hdc, x, y);
	int const r = GetRValue(color);
	int const g = GetGValue(color);
	int const b = GetBValue(color);

	if(!(r==255 and g ==0 and b == 255) and y < MAPSIZE_H and x>0 and x< MAPSIZE_W)
		return true;
	return false;
}

float const Physics_Manager::calc_landing_angle(unsigned const start_x, unsigned const selected_y, HDC const& hmapdc)
{
	long double leftpoint_x =start_x-2;
	long double leftpoint_y =0;
	long double rightpoint_x =static_cast<long double>(start_x)+2;
	long double rightpoint_y =0;
	bool letfpoint_isfound = false;
	bool rightpoint_isfound = false;

	for (unsigned j = selected_y-4; j < selected_y + 4; ++j)
	{
		if(!letfpoint_isfound)
		{
			if(Collide(hmapdc,static_cast<unsigned>(leftpoint_x),j))
			{
				leftpoint_y = j;
				letfpoint_isfound =true;
			}
		}
		if(!rightpoint_isfound)
		{
			if(Collide(hmapdc,static_cast<unsigned>(rightpoint_x),j))
			{
				rightpoint_y = j;
				rightpoint_isfound = true;
			}
		}
	}
	if(letfpoint_isfound and rightpoint_isfound)
	{
		long double i =atan((rightpoint_y-leftpoint_y)/(rightpoint_x-leftpoint_x));
		long double j =static_cast<float>( atan((rightpoint_y-leftpoint_y)/(rightpoint_x-leftpoint_x)));
		return static_cast<float>( atan((rightpoint_y-leftpoint_y)/(rightpoint_x-leftpoint_x)));
	}
	return 0.0f;

}


bool Physics_Manager::Collide_object(Object& obj, HDC const& hmapdc)
{
	unsigned const start_x = static_cast<const unsigned>(obj.getpos().x);//이미지 가운데 x좌표
	unsigned const start_y = static_cast<const unsigned>(obj.getpos().y+obj.getheight()/2);

	for (unsigned j = start_y; j < start_y + 4; ++j) 
	{

		if(Collide(hmapdc, start_x, j))
		{
			obj.moveto({obj.getpos().x, static_cast<float>(j- obj.getheight()/2)});
			obj.stop_move(calc_landing_angle(start_x,j,hmapdc));
			return true;
		}

	}
	return false;
}

void Physics_Manager::Collide_objects(std::vector<Tank>& tank,std::vector<Missile>& missile, HDC const& hmapdc)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			if (tank[i].is_falling())
				Collide_object(tank[i], hmapdc);
		}
	}
	if (!missile.empty())
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			if (missile[i].is_falling())
			{
				if (Collide_object(missile[i], hmapdc))
				{
					//부딪혔다면 폭발 후 제거
					missile[i].boom(hmapdc);
					missile.erase(missile.begin()+i);
				}
			}

		}
	}
}

void Physics_Manager::ballistics(std::vector<Tank>& tank,std::vector<Missile>& missile,float const delta)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			tank[i].ballistics_equation(delta);
			if (tank[i].is_out())
			{
				tank[i].take_damage(TANK_HP);
				tank[i].stop_move(0.0f);
			}

		}
	}
	if (!missile.empty())
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			missile[i].ballistics_equation(delta);
			//화면밖으로 나가면 제거
			if(missile[i].is_out())
				missile.erase(missile.begin()+i);


		}
	}
}
