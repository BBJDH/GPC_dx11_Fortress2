#include "Layout.hlsli"

namespace Shader
{
//t – SRV(셰이더 리소스 뷰)
//s – 샘플러
//u – UAV(순서가 지정되지 않은 액세스 뷰)
//b – CBV(상수 버퍼 보기)
    namespace Resource
    {
        cbuffer Transform : register(B0) { matrix World; };
        cbuffer Transform : register(B1) { matrix View; };
        cbuffer Transform : register(B2) { matrix Projection; };
    }

    Layout::Pixel Vertex(const Layout::Vertex Input)
    {
        Layout::Pixel Output =
        {
            Input.Position,
            Input.TexCoord
        };
        
        Output.Position = mul(Output.Position, Resource::World);
        Output.Position = mul(Output.Position, Resource::View);
        Output.Position = mul(Output.Position, Resource::Projection);

        return Output;
    }
    

}
