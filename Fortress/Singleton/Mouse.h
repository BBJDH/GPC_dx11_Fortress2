#pragma once
//#include"../stdafx.h"
#include"SingletonT.h"

class Mouse : public SingletonT<Mouse>
{
public:
	
	enum class POS_STATE 
	{
		Side_Left, Side_Right, Side_Up, Side_Down, 
		Side_LeftUP, Side_RightUP, Side_LeftDown, Side_RightDown, In_Window
	};
	LONG x;
	LONG y;//winÁÂÇ¥
	LONG coordinate_x;
	LONG coordinate_y;//È­¸é ÁßÁ¡ÀÌ 0,0 ÀÎ ÁÂÇ¥
public:
	Mouse();
	~Mouse() {};
	void convert_coodinate();
	POS_STATE getstate();

};

