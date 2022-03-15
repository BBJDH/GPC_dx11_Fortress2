#pragma once

class Object_Poolable
{
public:
	bool CanRecylcable = false;

public:
	virtual ~Object_Poolable() = default;

	virtual void recycle() //오브젝트 재사용시 호출
	{
		CanRecylcable = false;
	}
	
	virtual void set_recycle_able()  //오브젝트 수명이 다한 후 호출
	{
		CanRecylcable = true;
	}


	virtual void update()
	{
		if (CanRecylcable) return;
	}
};