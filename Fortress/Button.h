#pragma once
template<typename T>
class Button
{
public:
	enum class State
	{
		Activated, Collide, Clicked_Up, Toggled
	};
	Quadrangle collide_box;
	//Engine::Rendering::Image::UI deactivated_image;
	//Engine::Rendering::Image::UI activated_image;
	//Engine::Rendering::Image::UI collide_image;
	Engine::Rendering::Image::UI image;
	std::string name;

	
private:
	State state;
	std::function<T(void)> click_function; //Ŭ���� ������ �Լ�������
	std::function<bool(void)> function_button_on;	//��ư�� Ȱ��ȭ�� �Լ�������
	std::function<bool(void)> function_button_toggle;	//��ư�� Ȱ��ȭ�� �Լ�������
	bool on;

private:
	void set_button_image();
	bool activated();

public:
	Button();
	Button(std::function<T(void)> const & function, std::string const& name);

	void init_image_size(float const button_w, float const button_h);
	void init_image_location(float const button_x, float const button_y);
	void check_state();
	//��Ȱ��ȭ ���¶�� � ���۵� ��������,
	//��ۻ������� �ƴ����� Ȱ��ȭ(activated )���¿��� ����� ���

	bool clicked();
	bool get_on();
	T execute() const;
	void set_on(bool value);
	void bind_click_func(std::function<T(void)> const & function);
	void bind_activated_func(std::function<bool(void)> const & function);
	void bind_toggled_func(std::function<bool(void)> const & function);
};

