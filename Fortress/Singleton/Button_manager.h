#pragma once
#include"SingletonT.h"
class Button_manager :public SingletonT<Button_manager>
{
public:

private:
	//��ư�� ��ɵ��� ���⿡ ����
	//���� ���� ��ư, ĳ���� ���� ��ư, �÷��̾� �����ư, �� �����ư ��
	Scene * exit();  //����ȭ������ ���ư�


	//�Լ� �����ʹ� �ڵ念��, ������Ÿ�ӿ� ������
	//�Լ��������� ������ this call�� �Ҽ��� ����
	//funtional ����ؼ� ��ư �Է� ���� 
};
