#include "Layout.hlsli"

namespace Shader
{
    const Texture2D Resource : register(T0);
    cbuffer Value : register(b0)
    {
        float4 cbuffer_value;
    }
    
    Layout::Color Pixel(
        const Layout::Pixel Input) : SV_TARGET
    {
        Layout::Color Output =
        {
            Resource.Load(int3(Input.TexCoord.x, Input.TexCoord.y, 0))
        };
        //if (Output.a <0.1f)
        //    discard;
        //Output.a = cbuffer_value.a;
        float avr = (Output.r+Output.g+Output.b)/3.0f;
    	if (Input.TexCoord.y > cbuffer_value.y)
            return float4(avr,avr,avr, Output.a);

        return Output;
    }
        //���÷� ������Ʈ�� �ܰ����� ó�������ϴ� (���ø�)
//float4 �ڷ��� {x,y,z,alpha} ���۷� �޾Ƽ� (�� ������۴� �� �����Ӹ��� ����)
//x,y,z,�� Input�� ��ǥ��ҿ� ���Ͽ� �ȼ����� ����ϰ�
//alpha���� output�� a�� ����(��ÿ��� 1 �̴ϸ� �׸����� 0.5)

}
