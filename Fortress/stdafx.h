#pragma once
//공용 헤더
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<chrono>
#include<cassert>

//STL
#include<vector>
#include<string>



//=====================================
//	## 디파인문 ## (윈도우 초기화 셋팅)
//=====================================

//	전체화면 하고싶다면 밑에꺼 키자
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


//게임 세팅
#define CAM_SIZE_W 1280  //1280   //창의 크기가 아닌 창안에 표시할 해상도
#define CAM_SIZE_H 720  //720
#define MAPSIZE_W	 CAM_SIZE_W //1525*2//CAM_SIZE_W
#define MAPSIZE_H	 CAM_SIZE_H //1120*1.4//CAM_SIZE_H
#define BackgroundSIZE_W	CAM_SIZE_W //1525*2//CAM_SIZE_W//1280*1.2
#define BackgroundSIZE_H	CAM_SIZE_H //1120*1.4//CAM_SIZE_H//720*1.2
#define R_Image_SIZE 100
#define PLAYERS		 8
#define TANK_HP		 1000
#define OUT_RANGE	 100
#define FIRE_MIN_Length	 15



//UI 세팅
#define UI_SCREEN_SCROLL	4
#define UI_H				190*1.4
#define UI_POWER_X			282
#define UI_POWER_Y			550
#define UI_POWER_H			 15
#define UI_POWER_MUL		 4
#define UI_ANGLE_CENTER_X		92
#define UI_ANGLE_CENTER_Y		534
#define UI_ANGLE_MIN_Length		8
#define UI_ANGLE_MAX_Length		 60



//물리, 수학관련
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 6

//색상관련
#define Transparent_Color RGB(255, 0, 255)
#define Power_Color RGB(255, 0, 0)
#define GUIDE_ANGLE_Color RGB(255, 212, 0)




//=====================================
//	## 내가 만든 구조체 이곳에 추가 ##
//=====================================

//구조체
struct Position
{
	float x;
	float y;
};


//=====================================
//	## 엔진 헤더 파일 ##
//=====================================

#include "Engine/Physics.h"
#include "Engine/Rendering.h"
#include "Engine/Input.h"
#include "Engine/Game.h"
#include "Engine/Circle.h"
#include "Engine/Time.h"



//=====================================
//	## 내가 만든 헤더파일 이곳에 추가 ##
//=====================================

//게임안 보여질 객체들
#include"Object.h"
#include"Tank.h"
#include"Missile.h"

//랜덤추출함수
#include"Random.h"

//싱글톤 생성
#include"./Singleton/Mouse.h"
#include"./Singleton/Camera.h"
//#include"Turnmanager.h"

//메인 게임 클래스
#include "Fortress.h"

//Scene
#include "./Scene/Scene.h"
#include "./Scene/S_Battle.h"





//=====================================
//	## 싱글톤 추가 ##
//=====================================
#define _Mouse Mouse::get_singleton()
#define _CAM Camera::get_singleton()
//#define _Turn Turnmanager::get_singleton()





//===================================================
//	## 전역변수 ## (인스턴스, 윈도우핸들, 마우스좌표)
//===================================================
// 
// 나중에 사용해 보자
//extern HINSTANCE _hInstance;
//extern HWND _hWnd;
