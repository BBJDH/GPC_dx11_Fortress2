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

Asset 폴더 안에 사운드 폴더 생성

추가
_Sound->addsound()

일반적인 방법
_Sound->play("");

연사
_Sound->stop("");
_Sound->play("");

소리조절
_Sound->setvolume("");


*/