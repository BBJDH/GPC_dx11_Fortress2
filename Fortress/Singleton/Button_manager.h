#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
	struct slot_result
	{
		bool clicked; //새로운 슬롯 버튼이 눌렸는지
		int index;		//선택된 슬롯 번호
	}typedef result;
public:

	std::map < std::string, Button < Scene* >> scene_buttons;
	std::map < std::string, Button < bool >> nomal_buttons;
	std::vector < Button < bool >> slot_button;
	std::vector < Button < bool >> tank_button;
	
	//플레이어가 설정된 슬롯, 탱크, 색상
	std::vector<std::tuple< std::string, std::string, Color>> player_set;

private:
	//기본 설정
	//버튼 구현한 탱크는 반드시 여기에 기재(출력할 이미지명으로 들어감)
	std::string const tank_name[12] = { "canon","super", };
	//맵 버튼 문자 이미지 위치, 크기 설정
	std::string const map_name[3] = { "sky","friends","the artificial satellite"};
	int map_index=0;
	std::map <std::string, std::pair< _float2, _float2>> map_button_set;

private:
	//  ==================== Lobby ==================

	void check_buttons();
	result  slot_toggle(std::vector < Button < bool >>& slot_button);
	void set_slot_button(std::vector<Button<bool>>& slot,
		std::string const& location, _float2 const& position, _float2 const& size);
	void update_player_set();


public:

	//  ==================== Lobby ==================
	void init_map_button_set();
	void render_buttons();
	void render_tank_button_image();

	void    init_start_button();
	void    init_exit_button();
	void	init_map_button();
	void    init_slot_buttons();
	void    init_tank_buttons();
	void	update_map_button_text();
	
	//  ==================== Battle ==================
	std::string get_map_name();

	//버튼의 기능들을 여기에 나열
	//상점 가는 버튼, 캐릭터 선택 버튼, 플레이어 변경버튼, 맵 변경버튼 등
	
	
	//bool check_ready();
	class Scene * quit();  //시작화면으로 돌아감
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();
	bool  check_ready();
	bool  switch_map();
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

//활용
//template <typename... Ts>
//auto make_thing(Ts&&... xs)
//{
//	if constexpr (sizeof...(xs) == 2))
//	{
//	return std::make_pair(std::forward<Ts>(xs)...);
//	}
//	else
//	{
//		return std::make_tuple(std::forward<Ts>(xs)...);
//	}
//}