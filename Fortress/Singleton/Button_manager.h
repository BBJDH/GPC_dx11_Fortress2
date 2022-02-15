#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
public:
	enum class Scene_Func
	{
		Quit,Shop,Lobby,Battle,Bool_default //상점의 버튼들, 플레이어선택, 맵선택 버튼 등
	};
	std::map < std::string, Button < Scene* >> buttons;
	std::map < std::string, Button < bool >> slot_button;

public:
	//함수 포인터 바인딩하는 함수
	//template<typename T>
	//std::function<T(void)> bind_function(Scene_Func const scene_func);
	//

	//template<typename T>
	//std::function<T(void)> bind_function(std::function<T(void)> const func);

	
	//버튼의 기능들을 여기에 나열
	//상점 가는 버튼, 캐릭터 선택 버튼, 플레이어 변경버튼, 맵 변경버튼 등
	
	
	//bool check_ready();
	class Scene * quit();  //시작화면으로 돌아감
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();


	//함수 포인터는 코드영역, 컴파일타임에 정해짐
	//함수포인터의 단점은 this call을 할수가 없다
	//functional 사용해서 버튼 입력 구성 
};

//
//슬롯번호를 이름으로 가지는 슬롯 버튼
//8개이며 하나가 눌리면 다른 버튼은 모두비활성화
//슬롯 번호는 버튼이 눌렸다면 true를 반환, 활성화