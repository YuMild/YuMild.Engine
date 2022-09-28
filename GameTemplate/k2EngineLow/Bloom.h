#pragma once

namespace nsK2EngineLow
{
	class Bloom
	{
	public:
		/// <summary>
		/// ブルームを実行
		/// </summary>
		void Init();

		/// <summary>
		/// 輝度テクスチャ
		/// </summary>
		void InitLuminanceSprite();

		/// <summary>
		/// 輝度テクスチャにブラーを掛ける
		/// </summary>
		void InitBlurSprite();

		/// <summary>
		/// 最終合成するテクスチャ
		/// </summary>
		void InitFinalSprite();

		/// <summary>
		/// 最初
		/// </summary>
		void InitSprite();

		/// <summary>
		/// ブラー処理
		/// </summary>
		/// <param name="rc"></param>
		void Blur(RenderContext& renderContext);

		/// <summary>
		/// ブラー前のレンダー
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void Render(RenderContext& renderContext, RenderTarget& renderTarget);

		/// <summary>
		/// ブラー後のレンダー
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rt"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// 輝度テクスチャを描画
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