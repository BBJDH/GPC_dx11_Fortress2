#pragma once
#include "Object.h"


class Patterns : public Object
{
private:
	Engine::Rendering::Animation::Component ani;
	std::string name;
	bool recyclable;

public:
	~Patterns()override;
	Patterns(std::string const & name, _float2 const& pos);
	bool check_recyclable();
	
	void render();
	void recycle(std::string const& name, _float2 const& pos); //������Ʈ ����� ȣ��
	void set_recycle_able();  //������Ʈ ������ ���� �� ȣ��
};