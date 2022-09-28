#pragma once

namespace nsK2EngineLow
{
	class RenderingEngine
	{
	public:

		/// <summary>
		/// レンダーターゲットを作成
		/// </summary>
		void Init();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// 実行
		/// </summary>
		/// <param name="renderTarget"></param>
		void Execute(RenderContext& renderTarget);

		/// <summary>
		/// メインレンダリングターゲットを取得
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}

	private:

		RenderTarget m_mainRenderTarget;
	};

	extern RenderingEngine g_renderingEngine;
}
