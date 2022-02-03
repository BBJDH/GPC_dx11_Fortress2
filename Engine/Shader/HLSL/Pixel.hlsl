#include "Layout.hlsli"

namespace Shader
{
    const Texture2D Resource : register(T0);
    
    Layout::Color Pixel(const Layout::Pixel Input) : SV_TARGET
    {
        Layout::Color Output =
        {
            Resource.Load(int3(Input.TexCoord.x, Input.TexCoord.y, 0))
        };
    
    //float avr = (Output.r+Output.g+Output.b)/3.0f;
	//if (Input.TexCoord.y > 100)
 //       return float4(avr,avr,avr,1);

            //콘스턴트 버퍼 사용
        return Output;
    }
}