#include "stdafx.h"
#include "Physics_Manager.h"



unsigned const Physics_Manager::length(_float2 start, _float2 dest)
{
	return static_cast<unsigned const>(sqrt(pow((dest.x - start.x),2) + pow((dest.y - start.y),2)));
}

bool Physics_Manager::Collide(HDC const hdc, int const x, int const y)
{
	//pipeline -> 스왑체인 텍스쳐2d를 gdi로 가져와서 getpixel

	COLORREF const color = GetPixel(hdc, x, y);
	int const r = GetRValue(color);
	int const g = GetGValue(color);
	int const b = GetBValue(color);

	if(!(r==255 and g ==0 and b == 255) and y>0 and y < MAPSIZE_H and x>0 and x< MAPSIZE_W)
		return true;
	return false;
}

float const Physics_Manager::calc_landing_angle(unsigned const start_x, unsigned const selected_y, HDC const& hmapdc)
{
	long double leftpoint_x =start_x-Tank_Search_W;
	long double leftpoint_y =0;
	long double rightpoint_x =static_cast<long double>(start_x)+Tank_Search_W;
	long double rightpoint_y =0;
	bool letfpoint_isfound = false;
	bool rightpoint_isfound = false;

	for (unsigned j = selected_y-Tank_Search_H; j < selected_y + Tank_Search_H; ++j)
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

//낙하 계산
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

void Physics_Manager::Collide_objects(std::vector<Tank*>& tank,std::vector<Missile*>& missile, HDC const& hmapdc)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			tank[i]->check_state();
		}
	}
	if (!missile.empty())
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			unsigned const poistion_x = static_cast<const unsigned>(missile[i]->getpos().x);//이미지 가운데 x좌표
			unsigned const poistion_y = static_cast<const unsigned>(missile[i]->getpos().y + missile[i]->getheight() / 2);
			if (missile[i]->is_falling() and Collide(hmapdc, poistion_x, poistion_y))
			{
				//부딪혔다면 폭발 후 제거
				missile[i]->boom(hmapdc);  //맵파괴
				missile[i]->set_state(Missile::State::Collide);
				_Effect->push_effect(missile[i]->get_effect_type(), missile[i]->getpos());
				collide_bomb(*(missile[i]),tank);  //충돌판정
			}
		}
	}
}
// 탄도학 계산 
void Physics_Manager::ballistics(std::vector<Tank*>& tank,std::vector<Missile*>& missile,
	std::vector<Patterns>& patterns, float const delta)
{
	if (!tank.empty())
	{
		for (size_t i = 0; i < tank.size(); i++)
		{
			tank[i]->ballistics_equation(delta);
			if (tank[i]->is_out())
			{
				tank[i]->take_damage(TANK_HP);
				tank[i]->stop_move(0.0f);
			}
		}
	}
	if (!missile.empty())
	{
		for (size_t i = 0; i < missile.size(); i++)
		{
			missile[i]->ballistics_equation(delta,_Turn->get_wind());
			//화면밖으로 나갔거나 파괴되었을때
			if (missile[i]->is_out())
			{
				missile[i]->set_state(Missile::State::Delete);
			}
		}
	}
	if (!patterns.empty())
	{
		for (size_t i = 0; i < patterns.size(); i++)
		{
			patterns[i].ballistics_equation(delta,_Turn->get_wind());
			//화면밖으로 나가면 제거
			if (patterns[i].is_out())
				patterns.erase(patterns.begin() + i);
		}
	}
}

void Physics_Manager::collide_bomb(Missile const& missile, std::vector<Tank*>& tank)
{
	if (!tank.empty())
	{
		Engine::Physics::Component<Circle> bomb_circle;
		bomb_circle.Center = {missile.getpos().x-MAPSIZE_W/2,MAPSIZE_H/2-missile.getpos().y};
		bomb_circle.Radius = static_cast<float>(missile.get_range_w());

		for (size_t i = 0; i < tank.size(); i++)
		{
			Engine::Physics::Component<Quadrangle> tank_rect;
			tank_rect.Center = {tank[i]->getpos().x-MAPSIZE_W/2,MAPSIZE_H/2-tank[i]->getpos().y};
			tank_rect.Length = {static_cast<float const>(tank[i]->getwidth()),static_cast<float const>(tank[i]->getheight())};
			if (bomb_circle.Collide(tank_rect))
			{
				int const range = static_cast<int const>(missile.get_range_w());
				int const length = this->length(tank[i]->getpos(),missile.getpos());
				unsigned   dmg_mul =0;
				if((range - length) <=0)
					dmg_mul =1;
				else
					dmg_mul = range - length;
				 
				unsigned const dmg = missile.get_damage() * dmg_mul / range;

				tank[i]->ballistics_initialize(0,0);
				tank[i]->take_damage(dmg);
				tank[i]->ani_start();

				_CAM->earthquake_start();
			}
		}
	}
}

bool Physics_Manager::collide_button(Engine::Physics::Component<Quadrangle> const& button)
{
	Engine::Physics::Component<Point> point;
	point.x = static_cast<float>(_Mouse->x);
	point.y = static_cast<float>(_Mouse->y);

	return button.Collide(point);
}
