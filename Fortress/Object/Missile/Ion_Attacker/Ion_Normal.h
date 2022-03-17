#pragma once
class Ion_Normal : public Missile
{

private:
	void ani_set()override;	//¹Ù²î´Â³»¿ë

public:
	Ion_Normal(_float2 const& pos, unsigned const width, unsigned const height);
	~Ion_Normal()override;
};