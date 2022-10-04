#pragma once

#include "ShadowMapRender.h"

namespace nsK2EngineLow
{
	class RenderingEngine
	{
	public:

		/// <summary>
		/// 各種Initを実行
		/// </summary>
		void Init();

		/// <summary>
		/// レンダーターゲットを作成
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// シャドウマップレンダーを作成
		/// </summary>
		void InitShadowMapRender();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="renderContext"></param>
		void RenderToShadowMap(RenderContext& renderContext);

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
		ShadowMapRender m_shadowMapRender;
		RenderTarget m_mainRenderTarget;
	};

	extern RenderingEngine g_renderingEngine;
}
