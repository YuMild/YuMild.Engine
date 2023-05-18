#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;

	void RenderingEngine::Init()
	{
		InitMainRenderTarget();
	}

	void RenderingEngine::InitMainRenderTarget()
	{
		//RenderTarget.Create()を利用してレンダリングターゲットを作成する
		m_mainRenderTarget.Create(
			1600,                           //テクスチャの幅
			900,                            //テクスチャの長さ
			1,                              //Mipmapレベル
			1,                              //テクスチャ配列のサイズ
			DXGI_FORMAT_R32G32B32A32_FLOAT, //カラーバッファーのフォーマット
			DXGI_FORMAT_D32_FLOAT           //デプステンシルバッファーのフォーマット
		);
		g_postEffect.Init();
	}

	void RenderingEngine::Draw(RenderContext& renderContext)
	{
		RenderTarget* renderTargets[] =
		{
			&m_mainRenderTarget
		};

		//レンダリングターゲットとして利用できるまで待つ
		renderContext.WaitUntilToPossibleSetRenderTargets(1, renderTargets);

		//レンダリングターゲットを設定
		renderContext.SetRenderTargets(1, renderTargets);

		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetViews(1, renderTargets);

		//モデルをドロー
		g_engine->ExecuteRender();

		//レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTargets(1, renderTargets);

		m_modelRenderObject.clear();
	}

	void RenderingEngine::SpriteDraw(RenderContext& renderContext)
	{
		for (auto& sprite : m_spriteRenderObject)
		{
			sprite->Render(renderContext);
		}

		m_spriteRenderObject.clear();
	}

	void RenderingEngine::FontDraw(RenderContext& renderContext)
	{
		for (auto& font : m_fontRenderObject)
		{
			font->Render(renderContext);
		}

		m_fontRenderObject.clear();
	}

	void RenderingEngine::Execute(RenderContext& renderContext)
	{
		//モデルをドロー
		Draw(renderContext);
		//エフェクトをドロー
		EffectEngine::GetInstance()->Draw();
		//画像をドロー
		SpriteDraw(renderContext);
		//フォントをドロー
		FontDraw(renderContext);
	}
}