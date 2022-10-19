#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow
{

	Bloom g_bloom;

	void Bloom::Init()
	{
		InitLuminanceSprite();
		InitBlurSprite();
		InitFinalSprite();
		InitSprite();
	}

	void Bloom::InitLuminanceSprite()
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
		luminanceSpriteInitData.m_textures[0] = &g_renderingEngine.GetMainRenderTarget().GetRenderTargetTexture();
		//�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		
		//�쐬�����������������ƂɃX�v���C�g������������
		luminanceSprite.Init(luminanceSpriteInitData);
	}

	void Bloom::InitBlurSprite()
	{
		//�P�x�e�N�X�`���ɃK�E�V�A���u���[���|����
		gaussianBlur[0].Init(&g_postEffect.luminanceRenderTarget.GetRenderTargetTexture());
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

	void Bloom::InitSprite()
	{
		//�ŏI������̃e�N�X�`��
		SpriteInitData spriteInitData;
		spriteInitData.m_textures[0] = &g_renderingEngine.GetMainRenderTarget().GetRenderTargetTexture();
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;
		//�摜�`��p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//spriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		//�쐬�����������������ƂɃX�v���C�g������������
		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void Bloom::Blur(RenderContext& renderContext)
	{
		//�K�E�V�A���u���[��4����s����
		gaussianBlur[0].ExecuteOnGPU(renderContext, 5);
		gaussianBlur[1].ExecuteOnGPU(renderContext, 5);
		gaussianBlur[2].ExecuteOnGPU(renderContext, 5);
		gaussianBlur[3].ExecuteOnGPU(renderContext, 5);
	}

	void Bloom::Render(RenderContext& rc, RenderTarget& rt)
	{
		rc.WaitUntilToPossibleSetRenderTarget(rt);
		rc.SetRenderTargetAndViewport(rt);
		finalSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(rt);
	}

	void Bloom::Draw(RenderContext& rc)
	{
		copyToFrameBufferSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		copyToFrameBufferSprite.Draw(rc);
	}
}