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
//float4 자료형 {x,y,z,alpha} 버퍼로 받아서 (이 상수버퍼는 매 프레임마다 갱신)
//x,y,z,는 Input의 좌표요소와 비교하여 픽셀값을 계산하고
//alpha값은 output의 a에 대입(평시에는 1 미니맵 그릴때는 0.5)
}

