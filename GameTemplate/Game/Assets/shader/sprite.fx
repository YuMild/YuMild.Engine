cbuffer cb : register(b0){
	float4x4 mvp;
	float4 mulColor;
    float4 screenParam;
    float2 imageParam;
    int isRight = 0;
    int isUp = 0;
};

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}

float4 PSMain( PSInput In ) : SV_Target0
{
    if (isRight == 1)
    {
        if (In.pos.x > imageParam.x)
        {
            clip(-1);
        }
    }
    else if (isRight == 0)
    {
        if (In.pos.x < imageParam.x)
        {
            clip(-1);
        }
    }
    if (isUp == 1)
    {
        if (In.pos.y < imageParam.y)
        {
            clip(-1);
        }
    }
    else if (isUp == 0)
    {
        if (In.pos.y > imageParam.y)
        {
            clip(-1);
        }
    }
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}