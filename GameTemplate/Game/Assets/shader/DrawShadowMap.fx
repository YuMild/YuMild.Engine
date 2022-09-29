//�V���h�E�}�b�v�`��p�̃V�F�[�_�[

cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

struct SVSIn
{
    float4 pos      : POSITION;     // ���f���̒��_���W
    float3 normal   : NORMAL;       // �@��
    float2 uv       : TEXCOORD0;    // UV���W
};

struct SPSIn
{
    float4 pos      : SV_POSITION;  // �X�N���[����Ԃł̃s�N�Z���̍��W
    float3 normal   : NORMAL;       // �@��
    float2 uv       : TEXCOORD0;    // uv���W
};

Texture2D<float4> g_albedo : register(t0);      // �A���x�h�}�b�v
Texture2D<float4> g_shadowMap : register(t10);  // �V���h�E�}�b�v
sampler g_sampler : register(s0);               // �T���v���[�X�e�[�g

SPSIn VSMain(SVSIn vsIn)
{
    SPSIn psIn;
    psIn.pos = mul(mWorld, vsIn.pos);
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.uv = vsIn.uv;
    psIn.normal = mul(mWorld, vsIn.normal);
    return psIn;
}

float4 PSMain(SPSIn psIn) : SV_Target0
{
    return float4(psIn.pos.z, psIn.pos.z, psIn.pos.z, 1.0f);
}
