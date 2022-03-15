#pragma once

class Object_Poolable
{
public:
	bool CanRecylcable = false;

public:
	virtual ~Object_Poolable() = default;

	virtual void recycle() //������Ʈ ����� ȣ��
	{
		CanRecylcable = false;
	}
	
	virtual void set_recycle_able()  //������Ʈ ������ ���� �� ȣ��
	{
		CanRecylcable = true;
	}


	virtual void update()
	{
		if (CanRecylcable) return;
	}
};