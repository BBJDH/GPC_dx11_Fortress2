
#include"Camera.h"
#include"stdafx.h"

void Camera::up()
{
	pos.y += speed;
	if(pos.y >MAPSIZE_H/2-CAM_SIZE_H/2)
		pos.y = MAPSIZE_H/2-CAM_SIZE_H/2;
}

void Camera::down()
{
	pos.y -= speed;
	if(pos.y <-MAPSIZE_H/2+CAM_SIZE_H/2-UI_H/2)
		pos.y =-MAPSIZE_H/2+CAM_SIZE_H/2-UI_H/2;
}

void Camera::left()
{
	pos.x -= speed;
	if(pos.x <-MAPSIZE_W/2+CAM_SIZE_W/2)
		pos.x =-MAPSIZE_W/2+CAM_SIZE_W/2;
}

void Camera::right()
{
	pos.x += speed;
	if(pos.x  >MAPSIZE_W/2-CAM_SIZE_W/2)
		pos.x = MAPSIZE_W/2-CAM_SIZE_W/2;
}

Camera::Camera() :pos{ 0.0f,0.0f }, speed{UI_SCREEN_SCROLL}
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