Texture2D psTexture : TEXTURE : register(t0);
SamplerState psSamplerState : SAMPLER : register(s0);

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    float4 output;
    
    // Sample color from texture
    output = psTexture.Sample(psSamplerState, input.tex);
    
    return output;
}