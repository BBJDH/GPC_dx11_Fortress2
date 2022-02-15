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
	//�Լ� ������ ���ε��ϴ� �Լ�
	//template<typename T>
	//std::function<T(void)> bind_function(Scene_Func const scene_func);
	//

	//template<typename T>
	//std::function<T(void)> bind_function(std::function<T(void)> const func);

	
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	
	
	//bool check_ready();
	class Scene * quit();  //����ȭ������ ���ư�
	class Scene * to_lobby();
	class Scene * to_battle();
	bool  bool_func_default();


	//�Լ� �����ʹ� �ڵ念��, ������Ÿ�ӿ� ������
	//�Լ��������� ������ this call�� �Ҽ��� ����
	//functional ����ؼ� ��ư �Է� ���� 
};

//
//���Թ�ȣ�� �̸����� ������ ���� ��ư
//8���̸� �ϳ��� ������ �ٸ� ��ư�� ��κ�Ȱ��ȭ
//���� ��ȣ�� ��ư�� ���ȴٸ� true�� ��ȯ, Ȱ��ȭ