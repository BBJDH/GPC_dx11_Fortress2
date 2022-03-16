#pragma once
#include "Object.h"


class Patterns : public Object
{
private:
	Engine::Rendering::Animation::Component ani;
	std::string name;
	bool recyclable;
public:
	Patterns(std::string const & name, _float2 const& pos);
	void render();
	void recycle(); //������Ʈ ����� ȣ��
	void set_recycle_able();  //������Ʈ ������ ���� �� ȣ��
	~Patterns()override;
};