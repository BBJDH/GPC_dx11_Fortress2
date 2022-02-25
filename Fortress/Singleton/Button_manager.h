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
	void render();	//��ư ������Ʈ �� ������, ���� ���� ������Ʈ�ҳ����� �ִٸ�
					//���� �������� ����
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

	
	
	//  ==================== ��ư ��� ==================
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��

	class Scene * quit();  //����ȭ������ ���ư�
	class Scene * to_lobby();//�κ�� 
	class Scene * to_battle();//��ŸƮ��ư
	bool  switch_map();//�� ����Ī
	bool  set_power_guide();//�Ŀ� ���̵���α��

	//��ư Ȱ��ȭ �Լ�
	bool  bool_func_default();//��ư �⺻��
	bool  check_ready();//�÷��̾� ���̻����� Ȯ��




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