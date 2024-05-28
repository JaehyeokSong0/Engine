cbuffer CONSTANT_BUFFER : register(b0)
{
    // TEST Variables
    float xOffset;
    float yOffset;
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
    
    input.pos.x += xOffset;
    input.pos.y += yOffset;
    
    output.pos = float4(input.pos, 1.0f);
    output.tex = input.tex;
    return output;
}