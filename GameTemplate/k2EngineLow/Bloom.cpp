#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow
{

	Bloom g_bloom;

	void Bloom::InitBloom()
	{
		InitRenderTarget();
	}

	void Bloom::InitRenderTarget()
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

	void Bloom::InitLuminanceSprite(RenderTarget& renderTarget)
	{
		//�P�x���o�p�̃X�v���C�g�C�j�b�g�f�[�^���쐬
		SpriteInitData luminanceSpriteInitData;
		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		luminanceSpriteInitData.m_width = 1600;
		luminanceSpriteInitData.m_height = 900;
		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
		//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		
		//�쐬�����������������ƂɃX�v���C�g������������
		luminanceSprite.Init(luminanceSpriteInitData);
	}

	void Bloom::InitBlurSprite()
	{
		//�P�x�e�N�X�`���ɃK�E�V�A���u���[���|����
		gaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
		//gaussianBlur[0]�ɃK�E�V�A���u���[���|����
		gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
		//gaussianBlur[1]�ɃK�E�V�A���u���[���|����
		gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
		//gaussianBlur[2]�ɃK�E�V�A���u���[���|����
		gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());
	}

	void Bloom::InitFinalSprite()
	{
		//�ŏI�����p�̃X�v���C�g�C�j�b�g�f�[�^���쐬
		SpriteInitData finalSpriteInitData;
		//�{�P�e�N�X�`����4���w�肷��
		finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
		finalSpriteInitData.m_width = 1600;
		finalSpriteInitData.m_height = 900;
		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		finalSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
		//���Z�����ŕ`�悷��̂ŃA���t�@�u�����f�B���O���[�h�����Z�ɂ���
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		
		//�쐬�����������������ƂɃX�v���C�g������������
		finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::InitSprite(RenderTarget& renderTarget)
	{
		//�ŏI������̃e�N�X�`��
		SpriteInitData spriteInitData;
		spriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;
		//�摜�`��p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		//�쐬�����������������ƂɃX�v���C�g������������
		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void Bloom::BlurBeforeRender(RenderContext& renderContext)
	{
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);
		//�����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(luminanceRenderTarget);
		//�P�x���o���s��
		luminanceSprite.Draw(renderContext);
		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
	}

	void Bloom::Blur(RenderContext& renderContext)
	{
		//�K�E�V�A���u���[��4����s����
		gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
		gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
		gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
		gaussianBlur[3].ExecuteOnGPU(renderContext, 10);
	}

	void Bloom::BlurAfterRender(RenderContext& renderContext, RenderTarget& renderTarget)
	{
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		renderContext.WaitUntilToPossibleSetRenderTarget(renderTarget);
		//�����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(renderTarget);
		//�ŏI����
		finalSprite.Draw(renderContext);
		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		renderContext.WaitUntilFinishDrawingToRenderTarget(renderTarget);
		//���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		copyToFrameBufferSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		//�u���[���s�����e�N�X�`����`��
		copyToFrameBufferSprite.Draw(renderContext);
	}
}