#pragma once

namespace nsK2EngineLow
{
	class Bloom
	{
	public:
		/// <summary>
		/// ブルームを実行
		/// </summary>
		void InitBloom();

		/// <summary>
		/// レンダーターゲットを作成
		/// </summary>
		void InitRenderTarget();

		/// <summary>
		/// 最初
		/// </summary>
		void InitSprite(RenderTarget& renderTarget);

		/// <summary>
		/// 輝度テクスチャ
		/// </summary>
		void InitLuminanceSprite(RenderTarget& renderTarget);

		/// <summary>
		/// 輝度テクスチャにブラーを掛ける
		/// </summary>
		void InitBlurSprite();

		/// <summary>
		/// 最終合成するテクスチャ
		/// </summary>
		void InitFinalSprite();

		/// <summary>
		/// ブラー前のレンダー
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void BlurBeforeRender(RenderContext& renderContext);

		/// <summary>
		/// ブラー処理
		/// </summary>
		/// <param name="rc"></param>
		void Blur(RenderContext& renderContext);

		/// <summary>
		/// ブラー後のレンダー
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