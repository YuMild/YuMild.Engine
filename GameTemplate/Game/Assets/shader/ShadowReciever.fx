//影が落とされるモデル用のシェーダー

cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

cbuffer ShadowCb : register(b1)
{
    float4x4 mLVP;
};

struct SVSIn
{
    float4 pos      : POSITION;         // スクリーン空間でのピクセルの座標
    float3 normal   : NORMAL;           // 法線
    float2 uv       : TEXCOORD0;        // uv座標
};

struct SPSIn
{
    float4 pos      : SV_POSITION;      // スクリーン空間でのピクセルの座標
    float3 normal   : NORMAL;           // 法線
    float2 uv       : TEXCOORD0;        // uv座標

    float4 posInLVP : TEXCOORD1;        // ライトビュースクリーン空間でのピクセルの座標
};

Texture2D<float4> g_albedo : register(t0);      // アルベドマップ
Texture2D<float4> g_shadowMap : register(t10);  // シャドウマップ
sampler g_sampler : register(s0);               // サンプラーステート

SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    float4 worldPos = mul(mWorld, vsIn.pos);
    psIn.pos = mul(mView, worldPos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.uv = vsIn.uv;
    psIn.normal = mul(mWorld, vsIn.normal);

    psIn.posInLVP = mul(mLVP, worldPos);

    return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
    float4 color = g_albedo.Sample(g_sampler, psIn.uv);

    float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;

    float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;

    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
        && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {
        float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
        if (zInLVP > zInShadowMap +0.000025f)
        {
            color.xyz *= 0.5f;
        }
    }
    return color;
}
