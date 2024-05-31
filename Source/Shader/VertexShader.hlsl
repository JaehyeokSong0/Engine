cbuffer cbTransform : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct VS_INPUT
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION; // SV : System Value
    float2 tex : TEXCOORD;
};

VS_OUTPUT VSMain( VS_INPUT input)
{
    VS_OUTPUT output;
    
    output.pos = mul(float4(input.pos, 1.0f), World);
    output.pos = mul(output.pos, View);
    output.pos = mul(output.pos, Projection);

    output.tex = input.tex;
    
    return output;
}