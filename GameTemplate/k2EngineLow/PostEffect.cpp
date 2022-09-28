#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow
{
	PostEffect g_postEffect;

	void PostEffect::Init()
	{
		//輝度抽出用のレンダリングターゲットを作成
		luminanceRenderTarget.Create(
			1600,                           //テクスチャの幅
			900,                            //テクスチャの長さ
			1,                              //Mipmapレベル
			1,                              //テクスチャ配列のサイズ
			DXGI_FORMAT_R32G32B32A32_FLOAT, //カラーバッファーのフォーマット
			DXGI_FORMAT_D32_FLOAT           //デプステンシルバッファーのフォーマット
		);
	}

	void PostEffect::Render(RenderContext& renderContext)
	{
		RenderTarget* renderTargets[] =
		{
			&luminanceRenderTarget
		};

		renderContext.WaitUntilToPossibleSetRenderTargets(1, renderTargets);
		renderContext.SetRenderTargets(1, renderTargets);
		renderContext.ClearRenderTargetViews(1, renderTargets);

		g_bloom.LuminanceSpriteDraw(renderContext);

		renderContext.WaitUntilFinishDrawingToRenderTargets(1, renderTargets);

		g_bloom.Blur(renderContext);
		g_bloom.Render(renderContext, g_renderingEngine.GetMainRenderTarget());

		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		g_bloom.Draw(renderContext);
	};
};