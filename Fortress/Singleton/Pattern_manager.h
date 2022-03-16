#pragma once
#include"SingletonT.h"
class Pattern_manager :public SingletonT<Pattern_manager>
{
public:
    enum class Side
    {
        Up, Left, Right
    };

    std::vector<Patterns*> patterns;
private:

    std::string const pattern_name_list[2] = { "pinwheel","ufo" };
    float const pattern_gen_time = 0.3f;


    float interval = 0.0f;
    std::string pattern_name;

    //¹«´Ì Á¨ °£°Ý


private:

    void rand_pos(_float2 & pos);

public:
    Pattern_manager();
    ~Pattern_manager();
    void assign_pattern(float const delta);
    void recycle_pattern(std::string const& name, _float2 const & pos);
    void ballistics(float const delta);
};
