#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
public:
	enum class Scene_Func
	{
		Quit,Shop,Lobby,Battle,Bool_default //������ ��ư��, �÷��̾��, �ʼ��� ��ư ��
	};
	std::map < std::string, Button < Scene* >> buttons;
	std::map < std::string, Button < bool >> slot_button;


public:

	void check_buttons();
	
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	
	
	//bool check_ready();
	class Scene * quit();  //����ȭ������ ���ư�
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();
	void  slot_toggle();
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