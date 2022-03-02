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
	bool on;

private:
	void render();
	bool activated();

public:
	Button();
	Button(std::string const& name, std::function<T(void)> const& function);
	Button(std::string const& name, std::function<T(void)> const& onclick,
		std::function<bool(void)> const& active,_float2 const & position, _float2 const & length);
	void set_name(std::string const& name);
	void init_image_size(_float2 const& size);
	void init_image_location(_float2 const & postion);
	void update_state_and_render();
	//��Ȱ��ȭ ���¶�� � ���۵� ��������,
	//��ۻ������� �ƴ����� Ȱ��ȭ(activated )���¿��� ����� ���
	void make_clicked();
	bool clicked();
	bool get_on();
	T execute() const;
	void set_on(bool value);
	void bind_click_func(std::function<T(void)> const & function);
	void bind_activated_func(std::function<bool(void)> const & function);
	//void bind_toggled_func(std::function<bool(void)> const & function);
};

