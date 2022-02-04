#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
public:
	enum class Func
	{
		Shop,Exit,
	};
	//함수 포인터 바인딩하는 함수
	template<typename T>
	std::function<T(void)> bind_function(Func const state);

	
	//버튼의 기능들을 여기에 나열
	//상점 가는 버튼, 캐릭터 선택 버튼, 플레이어 변경버튼, 맵 변경버튼 등
	class Scene * exit();  //시작화면으로 돌아감


	//함수 포인터는 코드영역, 컴파일타임에 정해짐
	//함수포인터의 단점은 this call을 할수가 없다
	//functional 사용해서 버튼 입력 구성 
};
