///////////////////////////////////////
// 3D���f���p��GBuffer�ւ̕`��V�F�[�_�[
///////////////////////////////////////

#include "ModelVSCommon.h"

///////////////////////////////////////
// �\����
///////////////////////////////////////

// �s�N�Z���V�F�[�_�[�ւ̓���
struct SPSIn
{
    float4 pos : SV_POSITION;       //���W
    float3 normal : NORMAL;         //�@��
    float3 tangent : TANGENT;       //�ڃx�N�g��
    float3 biNormal : BINORMAL;     //�]�x�N�g��
    float2 uv : TEXCOORD0;          //UV���W
    float3 worldPos : TEXCOORD1;    //���[���h���W
};

cbuffer SkyCubeCb : register(b1)
{
    float luminance;                //���邳
};

///////////////////////////////////////
// �V�F�[�_�[���\�[�X
///////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);          //�A���x�h�}�b�v
Texture2D<float4> g_normal : register(t1);          //�@���}�b�v
Texture2D<float4> g_spacular : register(t2);        //�X�y�L�����}�b�v
TextureCube<float4> g_skyCubeMap : register(t10);

///////////////////////////////////////
// �T���v���[�X�e�[�g
///////////////////////////////////////
sampler g_sampler : register(s0);


////////////////////////////////////////////////
// �֐���`
////////////////////////////////////////////////

// �@���}�b�v����@�����擾�B
float3 GetNormalFromNormalMap(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 binSpaceNormal = g_normal.SampleLevel(g_sampler, uv, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

    float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

    return newNormal;
}

// ���f���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn);
    }
    else
    {
        m = mWorld;
    }

    psIn.pos = mul(m, vsIn.pos);            //���f���̒��_�����[���h���W�n�ɕϊ�
    psIn.worldPos = psIn.pos;               //���_�V�F�[�_�[���烏�[���h���W���o��

    psIn.pos = mul(mView, psIn.pos);        //���[���h���W�n����J�������W�n�ɕϊ�
    psIn.pos = mul(mProj, psIn.pos);        //�J�������W�n����X�N���[�����W�n�ɕϊ�
    psIn.normal = normalize(mul(m, vsIn.normal));
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
    psIn.uv = vsIn.uv;

    return psIn;
}

SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}

SPSIn VSMainSkin(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���[�֐��B
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    float4 albedoColor;
    float3 normal = normalize(psIn.normal);
    albedoColor = g_skyCubeMap.Sample(g_sampler, normal * -1.0f) * luminance;
    return albedoColor;
}
