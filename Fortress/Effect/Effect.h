#pragma once
class Effect
{
	//enum class Type 
	//{
	//	Circle, Ellipse
	//};
	
	//���, ��ġ, ������, ����ð� 
protected:
	Engine::Rendering::Animation::Component animation;
	std::string const name;
public:
	Effect(std::string const & location, _float2 const & position,
		_float2 const& size, float const duration);
	void render();
};