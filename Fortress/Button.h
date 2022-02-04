#pragma once
template<typename T>
class Button
{
public:
	enum class State
	{
		Normal, Collide, Clicked_Up,
	};
	Quadrangle collide_box;
	Engine::Rendering::Image::UI image;
	Engine::Rendering::Image::UI collide_image;
	
private:
	State state;
	std::function<T(void)> click_function;
	
public:
	Button();
	Button(std::function<T(void)> const & function);
	Button(std::string const& name, std::string const& clicked_name,
		float const location_x, float const location_y,
		float const length_x, float const length_y);

	bool clicked();
	T execute() const;
	void bind(std::function<T(void)> const & function);
	void check_state();
	void render();
};

