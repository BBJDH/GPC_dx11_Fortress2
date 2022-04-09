#pragma once
#include"SingletonT.h"
class Tank_manager :public SingletonT<Tank_manager>
{
public:
    std::string const tank_name[12] = { "Canon","Super","Ion_Attacker","Multi_Missile","Carrot","Missile_Tank","Secwind","Laser"};
    std::vector<Tank*> tanks;
    
private:
    void create_tank(_float2 const& position, std::string const& player_name, Tank::Tank_Type const tank_name, Color const color);
    void del_tank(Tank const * tank);

public:
    Tank_manager();
    ~Tank_manager();
    void create_tanks();
    void clear();
};

//
// 탱크 추가 절차
// 새로운 탱크 클래스 작성(스프라이트 폴더명 첫자 대문자 영문 형식 통일, 클래스 내부 enum클래스 탱크타입 기록)
// 미리 컴파일된 헤더에 추가
// 탱크클래스 enum 클래스 요소 추가
// 탱크 매니저 생성 case 추가, tank_name 배열에 요소(폴더명) 추가
// 미사일 스프라이트 폴더명 첫자 대문자 영문 형식 통일 작성(기능이 추가된경우 클래스 작성)
// 에셋 이미지 아이콘에도 미니 사이즈 이미지 추가
// 미사일 매니저 생성 case 추가
// ===이펙트 추가되는 경우=====
//  이펙트 enum 클래스 요소 추가, 스프라이트 작업
// 이펙트 매니저 생성 case 추가
// 
//