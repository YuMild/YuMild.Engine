#pragma once

namespace nsK2EngineLow
{
	class Bloom
	{
	public:
		/// <summary>
		/// �u���[�������s
		/// </summary>
		void InitBloom();

		/// <summary>
		/// �����_�[�^�[�Q�b�g���쐬
		/// </summary>
		void InitRenderTarget();

		/// <summary>
		/// �ŏ�
		/// </summary>
		void InitSprite(RenderTarget& renderTarget);

		/// <summary>
		/// �P�x�e�N�X�`��
		/// </summary>
		void InitLuminanceSprite(RenderTarget& renderTarget);

		/// <summary>
		/// �P�x�e�N�X�`���Ƀu���[���|����
		/// </summary>
		void InitBlurSprite();

		/// <summary>
		/// �ŏI��������e�N�X�`��
		/// </summary>
		void InitFinalSprite();

		/// <summary>
		/// �u���[�O�̃����_�[
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void BlurBeforeRender(RenderContext& renderContext);

		/// <summary>
		/// �u���[����
		/// </summary>
		/// <param name="rc"></param>
		void Blur(RenderContext& renderContext);

		/// <summary>
		/// �u���[��̃����_�[
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void BlurAfterRender(RenderContext& renderContext, RenderTarget& renderTarget);

		RenderTarget luminanceRenderTarget;
		GaussianBlur gaussianBlur[4];
		Sprite luminanceSprite;
		Sprite copyToFrameBufferSprite;
		Sprite finalSprite;
	};
	extern Bloom g_bloom;
}