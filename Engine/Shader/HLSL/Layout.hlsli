namespace Layout
{
    struct Vertex
    {
        float4 Position : POSITION;
        float2 TexCoord : TEXCOORD;
    };
    
    struct Pixel
    {
        float4 Position : SV_POSITION;
        float2 TexCoord : TEXCOORD;
    };
    
    typedef float4 Color;
}

//t – SRV(셰이더 리소스 뷰)
//s – 샘플러
//u – UAV(순서가 지정되지 않은 액세스 뷰)
//b – CBV(상수 버퍼 보기)