#pragma once
class Effect : public Object
{
	enum class State
	{
		Playing, Delete
	};

protected:
	//���� ���⿡ �߰�
	Engine::Rendering::Animation::Component animation;
	std::string const name;
	State state;
	float playtime;

protected:
	void check_state();
public:
	Effect(std::string const & location, _float2 const & position,
		_float2 const& size, float const duration);
	virtual ~Effect()=default;
	void render();
	State get_state();
};