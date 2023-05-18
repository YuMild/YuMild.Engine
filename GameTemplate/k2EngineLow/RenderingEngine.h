#pragma once

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
		/// モデルレンダーオブジェクトの数を追加
		/// </summary>
		/// <param name="modelRenderObject"></param>
		void AddModelRenderObject(ModelRender* modelRenderObject)
		{
			m_modelRenderObject.push_back(modelRenderObject);
		}

		/// <summary>
		/// スプライトレンダーオブジェクトの数の追加
		/// </summary>
		/// <param name="spriteRenderObject"></param>
		void AddSpriteRenderObject(SpriteRender* spriteRenderObject)
		{
			m_spriteRenderObject.push_back(spriteRenderObject);
		}

		/// <summary>
		/// フォントレンダーオブジェクトの数の追加
		/// </summary>
		/// <param name="spriteRenderObject"></param>
		void AddFontRenderObject(FontRender* fontRenderObject)
		{
			m_fontRenderObject.push_back(fontRenderObject);
		}

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// 画像の描画
		/// </summary>
		/// <param name="renderContext"></param>
		void SpriteDraw(RenderContext& renderContext);

		/// <summary>
		/// フォントの描画
		/// </summary>
		/// <param name="renderContext"></param>
		void FontDraw(RenderContext& renderContext);

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

		std::vector<ModelRender*>		m_modelRenderObject;
		std::vector<SpriteRender*>		m_spriteRenderObject;
		std::vector<FontRender*>		m_fontRenderObject;
		RenderTarget					m_mainRenderTarget;
	};

	extern RenderingEngine				g_renderingEngine;
}
