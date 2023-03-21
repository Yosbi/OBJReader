cbuffer WorldViewProjection: register(b0)
{
    matrix WVP;
};

struct VertexPosColor
{
    float3 Position : POSITION;
    float4 Color    : COLOR;
};

struct VertexShaderOutput
{
    float4 Color    : COLOR;
    float4 Position : SV_Position;
};

VertexShaderOutput main(VertexPosColor IN)
{
    VertexShaderOutput OUT;

    OUT.Position = mul(float4(IN.Position, 1.0f), WVP);
    OUT.Color = IN.Color;

    return OUT;
}