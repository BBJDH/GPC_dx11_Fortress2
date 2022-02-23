
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
//
//W = sin(2 * 3.14159f * (t * freq) + phase) * amp * (decaysec - t) / decaysec;
//
//t 현재 시간, amp(const) 진폭, freq(const) 진동수, phase(const) 위상, decaysec(const) 선형감쇄시간
//
//사실상 특별한 이론이 있다기 보다는 상황에 따라 감각적으로 각 상수를 정해서 표현하게 됩니다.^^
//* 진폭은 결과가 상하로 이동하는 정도가 되며 값이 클수록 더 크게 진동합니다.
//* 진동수는 초당 상하 운동하는 횟수로 값이 클수록 더 빨리 진동합니다.
//* 위상은 함수의 시작 포지션 정도로 실제로 값에 따른 느낌을 주는 것은 아니지만 함수들을 여러개 더할 때 좀 더 다양한 형태로 결과가 나옵니다. (사실상 주파수가 n 배로 할 경우 작은 주파수에서 항상 0가 되는 데, 위상을 주면 결과가 다르게 나옵니다. - 어차피 상수값을 감각적으로 넣는 데, 결과물에 다양함을 줄 수 있는 값 정도로 보면 될거 같습니다.)
//* 감쇄시간은 감쇄되는 함수모양에 따라 다른데, 어차피 모델링할 정확한 모양이 있는 게 아니므로 그냥 단순히 시간에 따라 감쇄한다고 설정하면 선형으로 하는 것도 별 문제는 없어 보입니다. (이 경우 t 가 decaysec 보다는 작거나 같아야 겠죠.)
//
//자 그럼 이걸로 어떻게 사용하냐 하면
//
//float t = (timeGetTime() - m_uWaveStartTime) * 0.001f;
//
//if (t < m_fDecayTime)
//{
//	camera.pivot.y += (sin(2.0f * 3.14159f * t * 3) * 30.0f +
//		sin(2.0f * 3.14159f * t * 7 + 0.2f) * 10.1f +
//		sin(2.0f * 3.14159f * t * 15 + 0.5f) * 1.1f))* (m_fDecayTime - t) / m_fDecayTime;
//}
//
//
//출처: https://blueasa.tistory.com/494 [Try & Error]