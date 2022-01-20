#pragma once
//���� ���
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<chrono>
#include<cassert>

//STL
#include<vector>
#include<string>


//=====================================
//	## ���� ���� ����ü �̰��� �߰� ##
//=====================================

//����ü
struct Position
{
	float x;
	float y;
};


//=====================================
//	## ���� ��� ���� ##
//=====================================

#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Engine/Game.h"
#include "Engine/Circle.h"



//=====================================
//	## ���� ���� ������� �̰��� �߰� ##
//=====================================

#include "Scene.h"
#include "S_Battle.h"
#include "Fortress.h"


//���Ӿ� ������ ��ü��
//#include"Tank.h"
//#include"Missile.h"

//���������Լ�
//#include"Random.h"

//�̱��� ����
#include"Mouse.h"
#include"Camera.h"
//#include"Turnmanager.h"

//=====================================
//	## �̱��� �߰� ##
//=====================================
#define _Mouse Mouse::get_singleton()
#define _CAM Camera::get_singleton()
#define _Turn Turnmanager::get_singleton()


//=====================================
//	## �����ι� ## (������ �ʱ�ȭ ����)
//=====================================

//	��üȭ�� �ϰ�ʹٸ� �ؿ��� Ű��
//#define FULLSCREEN

//#ifdef FULLSCREEN
//#define WINSTARTX 0
//#define WINSTARTY 0
//#define WINSIZE_X GetSystemMetrics(SM_CXSCREEN)
//#define WINSIZE_Y GetSystemMetrics(SM_CYSCREEN)
//#else 
//#define WINSTARTX 100
//#define WINSTARTY 0
//#define WINSIZE_X 1280  //1280
//#define WINSIZE_Y 720  //720
#define CAM_SIZE_X 1280  //1280
#define CAM_SIZE_Y 720  //720
//#endif // FULLSCREEN


//���� ����
#define R_Image_SIZE 100
#define MAPSIZE_W	 1500
#define MAPSIZE_H	 800
#define PLAYERS		 8
#define TANK_HP		 1000
#define OUT_RANGE	 100
#define FIRE_MIN_Length	 15



//UI ����
#define UI_SCREEN_SCROLL	30
#define UI_H				110
#define UI_POWER_X			282
#define UI_POWER_Y			550
#define UI_POWER_H			 15
#define UI_POWER_MUL		 4
#define UI_ANGLE_CENTER_X		92
#define UI_ANGLE_CENTER_Y		534
#define UI_ANGLE_MIN_Length		8
#define UI_ANGLE_MAX_Length		 60



//����, ���а���
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 6

//�������
#define Transparent_Color RGB(255, 0, 255)
#define Power_Color RGB(255, 0, 0)
#define GUIDE_ANGLE_Color RGB(255, 212, 0)



//===================================================
//	## �������� ## (�ν��Ͻ�, �������ڵ�, ���콺��ǥ)
//===================================================
// 
// ���߿� ����� ����
//extern HINSTANCE _hInstance;
//extern HWND _hWnd;
