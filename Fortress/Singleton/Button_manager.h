#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
public:
	enum class Color
	{
		Red, Blue, Green, Purple, Orange, Yellow ,Pink
	};//Brown
	std::map < std::string, Button < Scene* >> buttons;
	std::map < std::string, Button < bool >> slot_button;
	std::map < std::string, Button < bool >> tank_button;

	std::map<int, std::pair<std::string, Color> > player_set;

public:
	//��� 
	//������ ��ũ�� �ݵ�� ���⿡ ����(����� �̹��������� ��)
	std::string const tank_name[2] = { "canon","super", };

private:
	void check_buttons();
	
public:
	Scene* click_buttons();
	void  slot_toggle(std::map<std::string, Button < bool >>  & slot_button);
	
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	
	
	//bool check_ready();
	class Scene * quit();  //����ȭ������ ���ư�
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();
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