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
        
        return Output;
    //float avr = (Output.r+Output.g+Output.b)/3.0f;
	//if (Input.TexCoord.y > 100)
 //       return float4(avr,avr,avr,1);
    }
//float4 자료형 {x,y,z,alpha} 버퍼로 받아서 (이 상수버퍼는 매 프레임마다 갱신)
//x,y,z,는 Input의 좌표요소와 비교하여 픽셀값을 계산하고
//alpha값은 output의 a에 대입(평시에는 1 미니맵 그릴때는 0.5)

}
