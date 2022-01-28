#include "Mouse.h"
#include "stdafx.h"

Mouse::Mouse() :x{ CAM_SIZE_W/2 }, y{ CAM_SIZE_H/2 }, coordinate_x{0},coordinate_y{0}
{
}

void Mouse::convert_coodinate() //¸Ê ÁÂÇ¥°è·Î º¯È¯
{
	this->coordinate_x =  this->x - CAM_SIZE_W/2;
	this->coordinate_y = (CAM_SIZE_H-this->y) - CAM_SIZE_H/2;

}

Mouse::POS_STATE Mouse::getstate()
{
	if (x == 0 and y == 0) //¿ÞÀ§
		return POS_STATE::Side_LeftUP;
	else if (x >= CAM_SIZE_W-1 and y == 0)//¿À¸¥À§
		return POS_STATE::Side_RightUP;
	else if (x == 0 and y >= CAM_SIZE_H-1)//¿Þ¾Æ·¡
		return POS_STATE::Side_LeftDown;
	else if (x >= CAM_SIZE_W-1 and y >= CAM_SIZE_H-1)//¿À¸¥¾Æ·¡
		return POS_STATE::Side_RightDown;
	else if (x == 0)
		return POS_STATE::Side_Left;
	else if (x >= CAM_SIZE_W-1)
		return POS_STATE::Side_Right;
	else if (y == 0)
		return POS_STATE::Side_Up;
	else if (y >= CAM_SIZE_H-1)
		return POS_STATE::Side_Down;
	return POS_STATE::In_Window;


}
