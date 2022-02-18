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

	std::map < std::string, Button < Scene* >> buttons;
	std::vector < Button < bool >> slot_button;
	std::vector < Button < bool >> tank_button;

	//�÷��̾ ������ ����, ��ũ, ����
	std::vector<std::tuple<std::string,std::string, Color>> player_set;

public:
	//��� 
	//��ư ������ ��ũ�� �ݵ�� ���⿡ ����(����� �̹��������� ��)
	std::string const tank_name[12] = { "canon","super", };

private:
	//  ==================== Lobby ==================

	void check_buttons();
	result  slot_toggle(std::vector < Button < bool >>& slot_button);
	void set_slot_button(std::vector<Button<bool>>& slot,
		std::string const& location, _float2 const& position, _float2 const& size);
	void update_player_set();
	


public:
	void init_player_set();
	void render_buttons();
	

	//  ==================== Lobby ==================

	void    set_start_button();
	void    set_exit_button();
	void    set_slot_buttons();
	void    set_tank_buttons();


	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	
	
	//bool check_ready();
	class Scene * quit();  //����ȭ������ ���ư�
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();
	bool  check_ready();
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