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
	std::string const map_name[4] = { "sky","friends","the artificial satellite","the valley of city"};
	int map_index=0;
	std::map <std::string, std::pair< _float2, _float2>> map_button_set;

private:
	void	update_map_button_text();
	result  slot_toggle(std::vector < Button < bool >>& slot_button);
	void set_slot_button(std::vector<Button<bool>>& slot,
		std::string const& location, _float2 const& position, _float2 const& size);

	//  ==================== Lobby ==================

	void    init_map_button_set();
	void    init_start_button();
	void    init_exit_button();
	void	init_map_button();
	void    init_slot_buttons();
	void    init_tank_buttons();
	void    update_player_set();

	//  ==================== Battle ==================
	void    init_playing_exit_button();
	void    init_skip_button();
	void    init_power_arrow_button();
public:
	Scene* scene_button_on();
	void render();	//버튼 업데이트 후 렌더링, 만약 따로 업데이트할내용이 있다면
					//별도 씬에따라 만듬
	void clear_buttons();
	//void render_
	//  ==================== Lobby ==================
	void render_lobby_buttons();
	void render_tank_button_image();
	void init_lobby_buttons();

	
	//  ==================== Battle ==================
	std::string get_map_name();
	void	init_battle_buttons();
	void    init_gameover_exit_button();

	
	
	//  ==================== 버튼 기능 ==================
	//버튼의 기능들을 여기에 나열
	//상점 가는 버튼, 캐릭터 선택 버튼, 플레이어 변경버튼, 맵 변경버튼 등

	class Scene * quit();  //시작화면으로 돌아감
	class Scene * to_lobby();//로비로 
	class Scene * to_battle();//스타트버튼
	bool  switch_map();//맵 스위칭
	bool  set_power_guide();//파워 가이드라인기록

	//버튼 활성화 함수
	bool  bool_func_default();//버튼 기본셋
	bool  check_ready();//플레이어 둘이상인지 확인




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