#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
	struct slot_result
	{
		bool clicked; //���ο� ���� ��ư�� ���ȴ���
		int index;		//���õ� ���� ��ȣ
	}typedef result;
public:

	std::map < std::string, Button < Scene* >> scene_buttons;
	std::map < std::string, Button < bool >> nomal_buttons;
	std::vector < Button < bool >> slot_button;
	std::vector < Button < bool >> tank_button;
	
	//�÷��̾ ������ ����, ��ũ, ����
	std::vector<std::tuple< std::string, std::string, Color>> player_set;

private:
	//�⺻ ����
	//��ư ������ ��ũ�� �ݵ�� ���⿡ ����(����� �̹��������� ��)
	std::string const tank_name[12] = { "canon","super", };
	//�� ��ư ���� �̹��� ��ġ, ũ�� ����
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

	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	
	
	//bool check_ready();
	class Scene * quit();  //����ȭ������ ���ư�
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();
	bool  check_ready();
	bool  switch_map();
	//Ŭ���Ǹ� ������ ��۵�
	//���� �����ִ� ���� key(std::string)�� ����ϰ�
	//���ο� ��ư�� Ŭ���Ǹ� �ش����� ��� �� ���� �� off


	//�Լ� �����ʹ� �ڵ念��, ������Ÿ�ӿ� ������
	//�Լ��������� ������ this call�� �Ҽ��� ����
	//functional ����ؼ� ��ư �Է� ���� 
};

//
//���Թ�ȣ�� �̸����� ������ ���� ��ư
//8���̸� �ϳ��� ������ �ٸ� ��ư�� ��κ�Ȱ��ȭ
//���� ��ȣ�� ��ư�� ���ȴٸ� true�� ��ȯ, Ȱ��ȭ

//Ȱ��
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