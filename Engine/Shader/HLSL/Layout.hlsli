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
//float4 �ڷ��� {x,y,z,alpha} ���۷� �޾Ƽ� (�� ������۴� �� �����Ӹ��� ����)
//x,y,z,�� Input�� ��ǥ��ҿ� ���Ͽ� �ȼ����� ����ϰ�
//alpha���� output�� a�� ����(��ÿ��� 1 �̴ϸ� �׸����� 0.5)
}

