#pragma once
//공용 헤더
#include<iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include<Windows.h>
#include<math.h>
#include<time.h>
#include<chrono>
#include<cassert>
#include<functional>


//STL
#include<vector>
#include<string>
#include<map>

//=====================================
//	## 내가 만든 구조체 이곳에 추가 ##
//=====================================

//구조체, enum
struct _float2
{
	float x; 
	float y;
public:
	float width() const  { return x; } 
	float height() const { return y; }
	float value1() const { return x; }
	float value2() const { return y; }
};
enum class Color
{
	Red=0, Blue, Green, Purple, Orange, Yellow, Brown, Pink, White
};


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


//게임 해상도 세팅
#define CAM_SIZE_W 1280  //1280   //창의 크기가 아닌 창안에 표시할 해상도
#define CAM_SIZE_H 720  //720
#define MAPSIZE_W	 3000//CAM_SIZE_W
#define MAPSIZE_H	 1800//CAM_SIZE_H
#define MINIMAP_SIZE_W	 300
#define MINIMAP_SIZE_H	 180
#define BackgroundSIZE_W	CAM_SIZE_W*1.2//CAM_SIZE_W//1280*1.2
#define BackgroundSIZE_H	CAM_SIZE_H*1.2//CAM_SIZE_H//720*1.2


//시작화면 텍스트 세팅
#define TEXT_W 600
#define TEXT_H 50
#define TEXT_Location_Y 300




//이미지 애니메이션 크기
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

//플레이어수, 게임플레이 세팅
#define PLAYERS		 100
#define TANK_HP		 1000
#define TANK_DANGER_HP		 400
#define OUT_RANGE	 100
#define FIRE_MIN_Length	 15
#define FIRE_MUL		 2
#define Earthquake_POWER		 5
#define Earthquake_Cycle		 500.0f

//충돌관련
#define Tank_Step_H		 10  //탱크가 올라갈수 있는 높이
#define Tank_Search_H		 10  //지지각 계산할 높이값
#define Tank_Search_W		 4  //지지각 계산할 너비값



//UI 세팅
#define SCROLL_Per_Sec		1800
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


//애니매이션 재생시간 세팅

#define ANI_Tank_Nomal 4.1f
#define ANI_Tank_Idle 3.5f
#define ANI_Tank_Idle2 3.0f
#define ANI_Tank_Fire 0.25f
#define ANI_Tank_Move 0.1f
#define ANI_Tank_Fall 0.1f
#define ANI_Tank_Hit 2.0f
#define ANI_Tank_Danger 3.0f
#define ANI_Tank_Dead 3.0f
#define ANI_Tank_Stop 0.75f

#define ANI_Bomb_Throw 0.5f
#define ANI_Bomb_Boom 1.25f

//데미지 재생시간
#define Text_Damage_Show 3.0f

//물리, 수학관련
#define grav_accerl 9.8f //Gravialional accerleration
#define PI 3.141592f
#define Radian (PI/180.0f)
#define SPEED 8

//색상관련
#define Transparent_Color RGB(255, 0, 255)
#define Power_Color RGB(255, 0, 0)
#define GUIDE_ANGLE_Color RGB(255, 212, 0)



//===================================================
//	## 전역변수 ## (인스턴스, 윈도우핸들, 마우스좌표)
//===================================================
// 
// 나중에 사용해 보자
//extern HINSTANCE _hInstance;
//extern HWND _hWnd;

//=====================================
//	## 엔진 헤더 파일 ##
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
//	## 내가 만든 헤더파일 이곳에 추가 ##
//=====================================

//게임안 보여질 객체들

//상속
#include"Object/Object.h"
#include"Object/Effect/Effect.h"
#include"./Object/Missile/Missile.h"
#include"./Object/Tank/Tank.h"


//Tank
#include"./Object/Tank/Canon/Canon.h"
#include"./Object/Tank/Super/Super.h"


//Missile
#include"./Object/Missile/Canon/Canon_Normal.h"
#include"./Object/Missile/Canon/Canon_Special.h"
#include"./Object/Missile/Super/Super_Normal.h"
#include"./Object/Missile/Super/Super_Special.h"

//Effect
#include"Object/Effect/Effect_Normal.h"
#include"Object/Effect/Effect_Super_Normal.h"
#include"Object/Effect/Effect_Super_Special.h"

//기타 오브젝트 상속
#include"./Object/Patterns.h"

//버튼
#include"Button.h"

//랜덤추출함수
#include"Random.h"


//메인 게임 클래스
#include "Fortress.h"


//Scene
#include "./Scene/Scene.h"
#include "./Scene/S_Battle.h"
#include "./Scene/S_Start.h"
#include "./Scene//S_Lobby.h"

//매니저(싱글톤) 
#include"./Singleton/Tank_manager.h"
#include"./Singleton/Missile_manager.h"
#include"./Singleton/Mouse.h"
#include"./Singleton/Camera.h"
#include"./Singleton/Debug_manager.h"
#include"./Singleton/Image_manager.h"
#include"./Singleton/Physics_Manager.h"
#include"./Singleton/Map_manager.h"
#include"./Singleton/Turnmanager.h"
#include"./Singleton/Input_manager.h"
#include"./Singleton/Animation.h"
#include"./Singleton/Text_manager.h"
#include"./Singleton/Button_manager.h"
#include"./Singleton/Effect_manager.h"





//=====================================
//	## 싱글톤 추가 ##
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
#define _Button Button_manager::get_singleton()
#define _Text_manager Text_manager::get_singleton()
#define _Tank Tank_manager::get_singleton()
#define _Missile Missile_manager::get_singleton()
#define _Effect Effect_manager::get_singleton()

