#pragma once

class Object_Poolable
{
public:
	bool CanRecylcable = false;

public:
	virtual ~Object_Poolable() = default;

	virtual void SetRecycle()
	{
		CanRecylcable = true;
	}

	virtual void OnRecycle()
	{
		CanRecylcable = false;
	}

	virtual void Update()
	{
		if (CanRecylcable) return;
	}
};