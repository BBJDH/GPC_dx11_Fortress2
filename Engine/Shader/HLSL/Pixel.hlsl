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
        if (Output.r == 1 && Output.g == 0 && Output.b == 1)
            discard;
            
        return Output;
    }
}