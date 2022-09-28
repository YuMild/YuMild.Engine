#pragma once

namespace nsK2EngineLow
{
	class Bloom
	{
	public:
		/// <summary>
		/// �u���[�������s
		/// </summary>
		void Init();

		/// <summary>
		/// �P�x�e�N�X�`��
		/// </summary>
		void InitLuminanceSprite();

		/// <summary>
		/// �P�x�e�N�X�`���Ƀu���[���|����
		/// </summary>
		void InitBlurSprite();

		/// <summary>
		/// �ŏI��������e�N�X�`��
		/// </summary>
		void InitFinalSprite();

		/// <summary>
		/// �ŏ�
		/// </summary>
		void InitSprite();

		/// <summary>
		/// �u���[����
		/// </summary>
		/// <param name="rc"></param>
		void Blur(RenderContext& renderContext);

		/// <summary>
		/// �u���[�O�̃����_�[
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void Render(RenderContext& renderContext, RenderTarget& renderTarget);

		/// <summary>
		/// �u���[��̃����_�[
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// �P�x�e�N�X�`����`��
		/// </summary>
		/// <param name="rc"></param>
		void LuminanceSpriteDraw(RenderContext& rc)
		{
			luminanceSprite.Draw(rc);
		}

		GaussianBlur gaussianBlur[4];
		Sprite luminanceSprite;
		Sprite copyToFrameBufferSprite;
		Sprite finalSprite;
	};
	extern Bloom g_bloom;
}