#pragma once

#include "ModelRender.h"

namespace nsK2EngineLow
{
	class ShadowMapRender
	{
	public:

		/// <summary>
		/// シャドウマップ描画用のレンダリングターゲットを作成
		/// </summary>
		void Init();

		/// <summary>
		/// シャドウマップ描画用のモデルを作成
		/// </summary>
		/// <param name="filePath"></param>
		void DrawShadowModelInit(const char* filePath);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="rc"></param>
		void Render(RenderContext& renderContext);

		/// <summary>
		/// シャドウマップ作成用のカメラを取得
		/// </summary>
		/// <returns></returns>
		Camera& GetLightCamera()
		{
			return m_lightCamera;
		}

		/// <summary>
		/// レンダリングターゲットを取得
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetRenderTarget()
		{
			return m_shadowMap;
		}

	private:

		ModelRender m_modelRender;
		RenderTarget m_shadowMap;
		Camera m_lightCamera;
	};

	extern ShadowMapRender g_shadowMapRender;
}