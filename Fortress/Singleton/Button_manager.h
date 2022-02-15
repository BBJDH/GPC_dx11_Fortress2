#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
private:
public:
	enum class Func
	{
		Main_Title,Shop,Lobby,Battle //������ ��ư��, �÷��̾��, �ʼ��� ��ư ��
	};
	std::map < std::string, Button < Scene* >> buttons;


public:
	//�Լ� ������ ���ε��ϴ� �Լ�
	template<typename T>
	std::function<T(void)> bind_function(Func const state);

	
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	
	
	class Scene * to_main_title();  //����ȭ������ ���ư�
	class Scene * to_lobby();
	class Scene * to_battle();


	//�Լ� �����ʹ� �ڵ念��, ������Ÿ�ӿ� ������
	//�Լ��������� ������ this call�� �Ҽ��� ����
	//functional ����ؼ� ��ư �Է� ���� 
};
