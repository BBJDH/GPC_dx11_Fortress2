
#include"Camera.h"

#include"stdafx.h"

Camera::Camera() :pos{ 0.0f,0.0f },
pos_win{ (MAPSIZE_W - CAM_SIZE_W) / 2,(MAPSIZE_H - CAM_SIZE_H) / 2 },
speed{ SCROLL_Per_Sec }, speed_per_frame{0},
focus_w{ false }, focus_h{ false },
state{ State::Normal }, earthquake_time{ 0.0f }, pos0{ pos }
{}

void Camera::set_speed_per_frame(float const delta)
{
	speed_per_frame = static_cast<int>(speed * delta);
}

bool Camera::up(int const scroll)
{
	pos.y += scroll;
	pos_win.y -= scroll;

	if (pos.y > MAPSIZE_H / 2 - CAM_SIZE_H / 2)
	{
		pos.y = MAPSIZE_H/2-CAM_SIZE_H/2;
		//return false;
	}

	if (pos_win.y < 0)
	{
		pos_win.y = 0;
		return false;
	}
	return true;

}

bool Camera::down(int const scroll)
{
	pos.y -= scroll;
	pos_win.y += scroll;
	//if (pos.y < -(MAPSIZE_H / 2 + UI_H) + CAM_SIZE_H / 2)
	//{
	//	//return false;
	//}

	if (pos_win.y + CAM_SIZE_H > MAPSIZE_H + UI_H)
	{
		pos.y =-(MAPSIZE_H/2 + UI_H) + CAM_SIZE_H / 2 ;

		pos_win.y = MAPSIZE_H + UI_H - CAM_SIZE_H;
		return false;
	}
	return true;

}

bool Camera::left(int const scroll)
{
	pos.x -= scroll;
	pos_win.x -= scroll;
	//if (pos.x < -MAPSIZE_W / 2 + CAM_SIZE_W / 2)
	//{
	//	//return false;
	//}

	if (pos_win.x < 0)
	{
		pos.x =-MAPSIZE_W/2+CAM_SIZE_W/2;

		pos_win.x = 0;
		return false;
	}
	return true;

}

bool Camera::right(int const scroll)
{
	pos.x += scroll;
	pos_win.x += scroll;

	//if (pos.x > MAPSIZE_W / 2 - CAM_SIZE_W / 2)
	//{
	//	//return false;
	//}

	if (pos_win.x + CAM_SIZE_W > MAPSIZE_W)
	{
		pos.x = MAPSIZE_W/2-CAM_SIZE_W/2;

		pos_win.x = MAPSIZE_W - CAM_SIZE_W;
		return false;
	}
	return true;
}

Camera::State Camera::get_state() const
{
	return this->state;
}

void Camera::focusing(Object const& obj)
{
	//TODO: state 패턴으로 개선 필요,
	//포커싱시 시간에따른 속도로 변경 (프레임이 다르더라도 스크롤속도가 같도록)
	float const obj_x = obj.getpos().x-MAPSIZE_W/2;
	float const obj_y = MAPSIZE_H/2-obj.getpos().y;
	unsigned const next_step_x = static_cast<unsigned>(abs(obj_x - pos.x));
	unsigned const next_step_y = static_cast<unsigned>(abs(obj_y - pos.y));

	if (focus_w)
	{
		if (pos.x > obj_x) //카메라가 오브젝트 오른쪽
		{
			if (next_step_x < speed_per_frame)
			{
				left(next_step_x);
				focus_w = false;
			}

			else
				focus_w = left(speed_per_frame);
		}
		else//카메라가 오브젝트 왼쪽
		{
			if (next_step_x < speed_per_frame)
			{
				focus_w = right(next_step_x);
				focus_w = false;
			}

			else
				focus_w = right(speed_per_frame);
		}
	}
	if (focus_h)
	{
		if (pos.y > obj_y)//카메라가 위
		{
			if (next_step_y < speed_per_frame)
			{
				focus_h = down(next_step_y);
				focus_h = false;
			}

			else
				focus_h = down(speed_per_frame);
		}
		else
		{
			if (next_step_y < speed_per_frame)
			{
				focus_h = up(next_step_y);
				focus_h = false;
			}

			else
				focus_h = up(speed_per_frame);
		}
	}

}

void Camera::focus_on()
{
	focus_w = true;
	focus_h = true;
}


void Camera::move(Mouse::POS_STATE state)
{
	switch (state)
	{
	case Mouse::POS_STATE::Side_Up:        
	{
		up(speed_per_frame);
		return;
	}
	case Mouse::POS_STATE::Side_Left:      
	{
		left(speed_per_frame);
		return;
	}
	case Mouse::POS_STATE::Side_Right:     
	{
		right(speed_per_frame);
		return;
	}
	case Mouse::POS_STATE::Side_Down:      
	{
		down(speed_per_frame);
		return;
	}
	case Mouse::POS_STATE::Side_LeftUP:    
	{
		left(speed_per_frame);
		up(speed_per_frame);
		return; 
	}
	case Mouse::POS_STATE::Side_RightUP:   
	{
		right(speed_per_frame);
		up(speed_per_frame);
		return; 
	}
	case Mouse::POS_STATE::Side_LeftDown:  
	{
		left(speed_per_frame);
		down(speed_per_frame);
		return; 
	}
	case Mouse::POS_STATE::Side_RightDown: 
	{
		right(speed_per_frame);
		down(speed_per_frame);
		return; 
	}
	default: return;
	}
}

void Camera::earthquake_start()
{
	this->state = State::Earthquake;
	earthquake_time = 0.0f;
	pos0 = pos;

}

void Camera::earthquake()
{
	earthquake_time += Engine::Time::Get::Delta();
	int const val_x = static_cast<int const>(Earthquake_POWER*sin(earthquake_time * Earthquake_Cycle) * sqrt(1/earthquake_time));
	int const val_y = static_cast<int const>(Earthquake_POWER*sin(earthquake_time * Earthquake_Cycle) * sqrt(1/earthquake_time));
	if (earthquake_time < 0.8f)
	{
		if(val_x>0)
			right(val_x);
		else
			left(-val_x);
		if(val_y>0)
			up(val_y);
		else
			down(-val_y);
	}
	else
	{
		pos = pos0;
		this->state = State::Normal;
	}
}

void Camera::update()
{
	set_speed_per_frame(Engine::Time::Get::Delta());
	_CAM->move(_Mouse->getstate()); //마우스 위치에 따라 카메라 이동
	if (this->state == State::Earthquake)
	{
		earthquake();
	}
}
