//�e�����Ƃ���郂�f���p�̃V�F�[�_�[

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
    float4 pos : POSITION; // �X�N���[����Ԃł̃s�N�Z���̍��W
    float3 normal : NORMAL; // �@��
    float2 uv : TEXCOORD0; // uv���W
};

struct SPSIn
{
    float4 pos : SV_POSITION; // �X�N���[����Ԃł̃s�N�Z���̍��W
    float3 normal : NORMAL; // �@��
    float2 uv : TEXCOORD0; // uv���W

    float4 posInLVP : TEXCOORD1; // ���C�g�r���[�X�N���[����Ԃł̃s�N�Z���̍��W
};

Texture2D<float4> g_albedo : register(t0); // �A���x�h�}�b�v
Texture2D<float4> g_shadowMap : register(t10); // �V���h�E�}�b�v
sampler g_sampler : register(s0); // �T���v���[�X�e�[�g

//�f�B�U�p�^�[�����`����
static const int pattern[4][4] =
{
    { 0, 32, 8, 40 },
    { 48, 16, 56, 24 },
    { 12, 44, 4, 36 },
    { 60, 28, 52, 20 },
};

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
        if (zInLVP > zInShadowMap + 0.000025f)
        {
            color.xyz *= 0.5f;
        }
    }
    
    int x = (int) fmod(psIn.pos.x, 4.0f);
    int y = (int) fmod(psIn.pos.y, 4.0f);
    // ��ŋ��߂�x��y�𗘗p���Ă��̃s�N�Z���̃f�B�U�����O臒l���擾����
    int dither = pattern[y][x];
    // �f�B�U�����O臒l��50�ȉ��̃s�N�Z���̓s�N�Z���L������
    clip(dither - 50);
    
    return color;
}