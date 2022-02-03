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
#include "Engine/Input.h"
#include "Engine/Game.h"
#include "Engine/Circle.h"
#include "Engine/Quadrangle.h"
#include "Engine/Time.h"
#include "Engine/Pipeline.h"



//=====================================
//	## ���� ���� ������� �̰��� �߰� ##
//=====================================

//���Ӿ� ������ ��ü��
//#include"Object.h"
#include"Tank.h"
#include"Missile.h"
#include"Button.h"

//���������Լ�
#include"Random.h"

//�̱��� ����
#include"./Singleton/Mouse.h"
#include"./Singleton/Camera.h"
#include"./Singleton/Debug_manager.h"
#include"./Singleton/Image_manager.h"
#include"./Singleton/Physics_Manager.h"
#include"./Singleton/Map_manager.h"
#include"./Singleton/Turnmanager.h"
#include"./Singleton/Input_manager.h"
#include"./Singleton/Animation.h"

//#include"Turnmanager.h"

//���� ���� Ŭ����
#include "Fortress.h"

//Scene
#include "./Scene/Scene.h"
#include "./Scene/S_Battle.h"
#include "./Scene/S_Start.h"





//=====================================
//	## �̱��� �߰� ##
//=====================================
#define _Mouse Mouse::get_singleton()
#define _CAM Camera::get_singleton()
#define _Debug_manager Debug_manager::get_singleton()
#define _Image_manager Image_manager::get_singleton()
#define _Physics_manager Physics_Manager::get_singleton()
#define _Map_manager Map_manager::get_singleton()
#define _Turn Turnmanager::get_singleton()
#define _Input_manager Input_manager::get_singleton()
#define _Anime Animation::get_singleton()



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

//#endif // FULLSCREEN


//���� �ػ� ����
#define CAM_SIZE_W 1280  //1280   //â�� ũ�Ⱑ �ƴ� â�ȿ� ǥ���� �ػ�
#define CAM_SIZE_H 720  //720
#define MAPSIZE_W	 3000//CAM_SIZE_W
#define MAPSIZE_H	 1800//CAM_SIZE_H
#define BackgroundSIZE_W	MAPSIZE_W//CAM_SIZE_W//1280*1.2
#define BackgroundSIZE_H	MAPSIZE_H//CAM_SIZE_H//720*1.2


//����ȭ�� �ؽ�Ʈ ����
#define TEXT_W 600
#define TEXT_H 50
#define TEXT_Location_Y 300




//�̹��� �ִϸ��̼� ũ��
//#define R_Image_SIZE 100
#define Tank_SIZE 50
#define Tank_ANI_SIZE 250
#define Missile_SIZE 150
#define Missile_Explosion_SIZE 300
#define UI_Arrow_SIZE 100
#define UI_Arrow_Location_H 60
#define Tank_HP_Bar_W 60
#define Tank_HP_Bar_H 10
#define Tank_HP_Bar_Location_H 30
#define Tank_HP_Bar_Location_W 30
#define Tank_HP_Bar_Mul 0.06

//�÷��̾��, �����÷��� ����
#define PLAYERS		 2
#define TANK_HP		 1000
#define TANK_DANGER_HP		 400
#define OUT_RANGE	 100
#define FIRE_MIN_Length	 15
#define FIRE_MUL		 1.5
#define Earthquake_POWER		 20
#define Earthquake_Cycle		 1000.0f

//�浹����
#define Tank_Step_H		 10  //��ũ�� �ö󰥼� �ִ� ����
#define Tank_Search_H		 10  //������ ����� ���̰�
#define Tank_Search_W		 4  //������ ����� �ʺ�



//UI ����
#define UI_SCREEN_SCROLL	10
#define UI_H				130 //1930
#define UI_Bar_X			450
#define UI_Bar_H			 20

#define UI_HP_Y				642
#define UI_POWER_Y			669
#define UI_FUEL_Y			695

#define UI_POWER_MUL		 5
#define UI_POWER_MAX		 128
#define UI_HP_MUL			 0.64
#define UI_Fuel_MUL			 6.4
#define UI_ANGLE_CENTER_X		150
#define UI_ANGLE_CENTER_Y		642
//#define UI_ANGLE_MIN_Length		8
#define UI_ANGLE_Length		 35


//�ִϸ��̼� ����ð� ����

#define ANI_Tank_Nomal 4.1f
#define ANI_Tank_Idle 3.5f
#define ANI_Tank_Idle2 3.0f
#define ANI_Tank_Fire 0.25f
#define ANI_Tank_Move 0.1f
#define ANI_Tank_Fall 0.1f
#define ANI_Tank_Danger 3.0f
#define ANI_Tank_Dead 3.0f
#define ANI_Tank_Stop 0.75f

#define ANI_Bomb_Throw 0.5f
#define ANI_Bomb_Boom 1.25f

//����, ���а���
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 8

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
