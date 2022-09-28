#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;

	void RenderingEngine::Init()
	{
		//RenderTarget.Create()�𗘗p���ă����_�����O�^�[�Q�b�g���쐬����
		m_mainRenderTarget.Create(
			1600,                           //�e�N�X�`���̕�
			900,                            //�e�N�X�`���̒���
			1,                              //Mipmap���x��
			1,                              //�e�N�X�`���z��̃T�C�Y
			DXGI_FORMAT_R32G32B32A32_FLOAT, //�J���[�o�b�t�@�[�̃t�H�[�}�b�g
			DXGI_FORMAT_D32_FLOAT           //�f�v�X�e���V���o�b�t�@�[�̃t�H�[�}�b�g
		);
		g_postEffect.Init();
	}

	void RenderingEngine::Draw(RenderContext& renderContext)
	{
		RenderTarget* renderTargets[] =
		{
			&m_mainRenderTarget
		};

		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		renderContext.WaitUntilToPossibleSetRenderTargets(1, renderTargets);

		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargets(1, renderTargets);

		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetViews(1, renderTargets);

		//���f�����h���[
		g_engine->ExecuteRender();

		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		renderContext.WaitUntilFinishDrawingToRenderTargets(1, renderTargets);
	}

	void RenderingEngine::Execute(RenderContext& renderContext)
	{
		Draw(renderContext);
		g_postEffect.Render(renderContext);
	}
}