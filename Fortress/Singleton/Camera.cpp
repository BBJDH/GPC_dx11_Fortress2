
#include"Camera.h"
#include"../stdafx.h"
#include"stdafx.h"

void Camera::up()
{
	pos.y += speed;
	pos_win.y -= speed;

	if (pos.y > MAPSIZE_H / 2 - CAM_SIZE_H / 2)
		pos.y = MAPSIZE_H/2-CAM_SIZE_H/2;

	if (pos_win.y < 0)
		pos_win.y = 0;
}

void Camera::down()
{
	pos.y -= speed;
	pos_win.y += speed;
	if (pos.y < -MAPSIZE_H / 2 + CAM_SIZE_H / 2 - UI_H / 2)
		pos.y =-MAPSIZE_H/2+CAM_SIZE_H/2-UI_H/2;

	if (pos_win.y + CAM_SIZE_H > MAPSIZE_H + UI_H)
		pos_win.y = MAPSIZE_H + UI_H - CAM_SIZE_H;
}

void Camera::left()
{
	pos.x -= speed;
	pos_win.x -= speed;
	if (pos.x < -MAPSIZE_W / 2 + CAM_SIZE_W / 2)
		pos.x =-MAPSIZE_W/2+CAM_SIZE_W/2;

	if (pos_win.x < 0)
		pos_win.x = 0;
}

void Camera::right()
{
	pos.x += speed;
	pos_win.x += speed;
	
	if (pos.x > MAPSIZE_W / 2 - CAM_SIZE_W / 2)
		pos.x = MAPSIZE_W/2-CAM_SIZE_W/2;

	if (pos_win.x + CAM_SIZE_W > MAPSIZE_W)
		pos_win.x = MAPSIZE_W - CAM_SIZE_W;

}

Camera::Camera() :pos{ 0.0f,0.0f }, pos_win{ (MAPSIZE_W - CAM_SIZE_W)/2,(MAPSIZE_H - CAM_SIZE_H) / 2 }, speed{ UI_SCREEN_SCROLL }
{}

void Camera::move(Mouse::POS_STATE state)
{
	switch (state)
	{
	case Mouse::POS_STATE::Side_Up:        
	{
		up();
		return;
	}
	case Mouse::POS_STATE::Side_Left:      
	{
		left();
		return;
	}
	case Mouse::POS_STATE::Side_Right:     
	{
		right();
		return;
	}
	case Mouse::POS_STATE::Side_Down:      
	{
		down();
		return;
	}
	case Mouse::POS_STATE::Side_LeftUP:    
	{
		left();
		up();
		return; 
	}
	case Mouse::POS_STATE::Side_RightUP:   
	{
		right();
		up();
		return; 
	}
	case Mouse::POS_STATE::Side_LeftDown:  
	{
		left();
		down();
		return; 
	}
	case Mouse::POS_STATE::Side_RightDown: 
	{
		right();
		down();
		return; 
	}
	default: return;
	}
}