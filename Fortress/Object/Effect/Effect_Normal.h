#pragma once
class Effect_Normal : public Effect
{

private:
	float const explosion_time = 0.7f;
public:
	Effect_Normal(_float2 const & position);
	~Effect_Normal() override;
};