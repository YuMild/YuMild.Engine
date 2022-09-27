#pragma once
namespace nsK2EngineLow
{
	class PostEffect
	{
	public:
		/// <summary>
		/// ポストエフェクトを作成
		/// </summary>
		void Init();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc"></param>
		void Render(RenderContext& rc);

		RenderTarget luminanceRenderTarget;
	};
	extern PostEffect g_postEffect;
}