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
	//�Լ� ������ ���ε��ϴ� �Լ�
	template<typename T>
	std::function<T(void)> bind_function(Func const state);

	
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	class Scene * exit();  //����ȭ������ ���ư�


	//�Լ� �����ʹ� �ڵ念��, ������Ÿ�ӿ� ������
	//�Լ��������� ������ this call�� �Ҽ��� ����
	//functional ����ؼ� ��ư �Է� ���� 
};
