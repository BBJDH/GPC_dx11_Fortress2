#pragma once
#include"SingletonT.h"

class Sound_manager : public SingletonT<Sound_manager>
{
public:
	struct Sound_Node
	{
		//FMOD::Sound* sound;
		//FMOD::Channel* channel;
	};
private:
public:
	Sound_manager();
	void AddSound();


	//play stop resume 
};


/*

Asset ���� �ȿ� ���� ���� ����

�߰�
_Sound->addsound()

�Ϲ����� ���
_Sound->play("");

����
_Sound->stop("");
_Sound->play("");

�Ҹ�����
_Sound->setvolume("");


*/