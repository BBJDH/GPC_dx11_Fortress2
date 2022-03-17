#pragma once
#include"SingletonT.h"
class Tank_manager :public SingletonT<Tank_manager>
{
public:
    std::string const tank_name[12] = { "Canon","Super","Ion_Attacker",};
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
// 새로운 탱크 클래스 작성(스프라이트 폴더명 첫자 대문자 영문 형식 통일)
// 탱크클래스 enum 클래스 요소 추가
// 탱크 매니저 생성 case 추가, tank_name 배열에 요소(폴더명) 추가
// 미사일클래스 작성(스프라이트 폴더명 첫자 대문자 영문 형식 통일)
// 미사일클래스 enum 클래스 요소 추가
// 미사일 매니저 생성 case 추가
// 이펙트 enum 클래스 요소 추가
// 이펙트 매니저 생성 case 추가
// 
//