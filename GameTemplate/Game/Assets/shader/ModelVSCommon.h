//���f���̒��_�V�F�[�_�[�֌W�̋��ʃw�b�_�[

///////////////////////////////////////
// �萔�o�b�t�@�B
///////////////////////////////////////
// ���f���p�̒萔�o�b�t�@�[
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

////////////////////////////////////////////////
// �\����
////////////////////////////////////////////////

// ���_�V�F�[�_�[�ւ̓���
struct SVSIn
{
    float4 pos : POSITION;          //���_���W�B
    float3 normal : NORMAL;         //�@���B
    float2 uv : TEXCOORD0;          //UV���W�B
    float3 tangent : TANGENT;      //�ڃx�N�g���B
    float3 biNormal : BINORMAL;     //�]�x�N�g���B
    int4  Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

////////////////////////////////////////////////
// �O���[�o���ϐ��B
////////////////////////////////////////////////
StructuredBuffer<float4x4> g_boneMatrix         : register(t3);	    //�{�[���s��B
StructuredBuffer<float4x4> g_worldMatrixArray   : register(t10);	//���[���h�s��̔z��B�C���X�^���V���O�`��̍ۂɗL���B
////////////////////////////////////////////////
// �֐���`�B
////////////////////////////////////////////////

/// <summary>
//�X�L���s����v�Z����B
/// </summary>
float4x4 CalcSkinMatrix(SVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
    [unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}
