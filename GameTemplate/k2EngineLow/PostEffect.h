#pragma once
namespace nsK2EngineLow
{
	class PostEffect
	{
	public:
		/// <summary>
		/// �|�X�g�G�t�F�N�g���쐬
		/// </summary>
		void Init();

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc"></param>
		void Render(RenderContext& rc);

		RenderTarget luminanceRenderTarget;
	};
	extern PostEffect g_postEffect;
}