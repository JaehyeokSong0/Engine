// Vertex Shader input.
struct VSInput
{
    float3 position : POSITION;
};

// Pixel Shader input.
struct VSToPS
{
    float4 position: SV_POSITION;
};

// Vertex Shader.
VSToPS vsmain(VSInput input)
{
    VSToPS output;
    output.position = float4(input.position, 1.0f);
    
    return output;
}

// Pixel shader.
float4 psmain(VSToPS input) : SV_Target
{
    return float4(1, 1, 0, 1);
}