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
        //샘플러 스테이트로 외곽선을 처리가능하다 (샘플링)
//float4 자료형 {x,y,z,alpha} 버퍼로 받아서 (이 상수버퍼는 매 프레임마다 갱신)
//x,y,z,는 Input의 좌표요소와 비교하여 픽셀값을 계산하고
//alpha값은 output의 a에 대입(평시에는 1 미니맵 그릴때는 0.5)

}
