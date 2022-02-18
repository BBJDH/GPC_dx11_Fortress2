#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
public:

	std::map < std::string, Button < Scene* >> buttons;
	std::map < std::string, Button < bool >> slot_button;
	std::map < std::string, Button < bool >> tank_button;

	//이름, 탱크, 색상
	std::map<int, std::tuple<std::string, std::string, Color> > player_set;

public:
	//상수 
	//버튼 구현한 탱크는 반드시 여기에 기재(출력할 이미지명으로 들어감)
	std::string const tank_name[12] = { "canon","super", };

private:
	void check_buttons();
	void update_player_set();
	
public:
	void init_player_set();
	void render_buttons();
	std::string  slot_toggle(std::map<std::string, Button < bool >>  & slot_button);
	
	//버튼의 기능들을 여기에 나열
	//상점 가는 버튼, 캐릭터 선택 버튼, 플레이어 변경버튼, 맵 변경버튼 등
	
	
	//bool check_ready();
	class Scene * quit();  //시작화면으로 돌아감
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();
	//클릭되면 슬롯이 토글됨
	//기존 켜져있던 슬롯 key(std::string)를 기억하고
	//새로운 버튼이 클릭되면 해당을롯 토글 온 기존 것 off


	//함수 포인터는 코드영역, 컴파일타임에 정해짐
	//함수포인터의 단점은 this call을 할수가 없다
	//functional 사용해서 버튼 입력 구성 
};

//
//슬롯번호를 이름으로 가지는 슬롯 버튼
//8개이며 하나가 눌리면 다른 버튼은 모두비활성화
//슬롯 번호는 버튼이 눌렸다면 true를 반환, 활성화