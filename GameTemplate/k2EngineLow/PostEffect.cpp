#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow
{
	PostEffect g_postEffect;

	void PostEffect::Init()
	{
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
		luminanceRenderTarget.Create(
			1600,                           //�e�N�X�`���̕�
			900,                            //�e�N�X�`���̒���
			1,                              //Mipmap���x��
			1,                              //�e�N�X�`���z��̃T�C�Y
			DXGI_FORMAT_R32G32B32A32_FLOAT, //�J���[�o�b�t�@�[�̃t�H�[�}�b�g
			DXGI_FORMAT_D32_FLOAT           //�f�v�X�e���V���o�b�t�@�[�̃t�H�[�}�b�g
		);
	}
}