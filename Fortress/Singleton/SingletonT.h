#pragma once
template <typename T>
class SingletonT
{//crtp ����
protected:
	//�̱��� �ν��Ͻ� ����
	//static���� �ѹ��� �����ǵ��� �ۼ�
	static T * singleton_instance;
	SingletonT() {};
	~SingletonT() {};

public:
	//������ �ν��Ͻ� ��ȯ
	static T* get_singleton();
	//������ �ν��Ͻ� �޸𸮿��� ����
	void release_singleton();

};

//����

//�ν��Ͻ� ����
template<typename T>
T* SingletonT<T>::singleton_instance = nullptr;

//�̱��� �ν��Ͻ� ��ȯ
template<typename T>
T* SingletonT<T>::get_singleton()
{
	if (singleton_instance == nullptr)
		singleton_instance = new T;
	return singleton_instance;
}
//������ �ν��Ͻ� �޸𸮿��� ����
template<typename T>
void SingletonT<T>::release_singleton()
{
	if (singleton_instance != nullptr)
	{
		delete singleton_instance;
		singleton_instance = nullptr;
	}
}