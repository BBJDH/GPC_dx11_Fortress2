#include "Mouse.h"
#include "stdafx.h"

Mouse::Mouse() :x{ 0 }, y{0}
{
}

Mouse::POS_STATE Mouse::getpos()
{
	if (x == 0 and y == 0) //����
		return POS_STATE::Side_LeftUP;
	else if (x >= CAM_SIZE_W-1 and y == 0)//������
		return POS_STATE::Side_RightUP;
	else if (x == 0 and y >= CAM_SIZE_H-1)//�޾Ʒ�
		return POS_STATE::Side_LeftDown;
	else if (x >= CAM_SIZE_W-1 and y >= CAM_SIZE_H-1)//�����Ʒ�
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
