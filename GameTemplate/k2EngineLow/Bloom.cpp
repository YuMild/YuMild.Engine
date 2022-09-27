#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow
{

	Bloom g_bloom;

	void Bloom::InitBloom()
	{
		InitRenderTarget();
	}

	void Bloom::InitRenderTarget()
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

	void Bloom::InitLuminanceSprite(RenderTarget& renderTarget)
	{
		//輝度抽出用のスプライトイニットデータを作成
		SpriteInitData luminanceSpriteInitData;
		//輝度抽出用のシェーダーのファイルパスを指定する
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		//頂点シェーダーのエントリーポイントを指定する
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		//ピクセルシェーダーのエントリーポイントを指定する
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		luminanceSpriteInitData.m_width = 1600;
		luminanceSpriteInitData.m_height = 900;
		//テクスチャはメインレンダリングターゲットのカラーバッファー
		luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
		//描き込むレンダリングターゲットのフォーマットを指定する
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		
		//作成した初期化情報をもとにスプライトを初期化する
		luminanceSprite.Init(luminanceSpriteInitData);
	}

	void Bloom::InitBlurSprite()
	{
		//輝度テクスチャにガウシアンブラーを掛ける
		gaussianBlur[0].Init(&luminanceRenderTarget.GetRenderTargetTexture());
		//gaussianBlur[0]にガウシアンブラーを掛ける
		gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
		//gaussianBlur[1]にガウシアンブラーを掛ける
		gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
		//gaussianBlur[2]にガウシアンブラーを掛ける
		gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());
	}

	void Bloom::InitFinalSprite()
	{
		//最終合成用のスプライトイニットデータを作成
		SpriteInitData finalSpriteInitData;
		//ボケテクスチャを4枚指定する
		finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
		finalSpriteInitData.m_width = 1600;
		finalSpriteInitData.m_height = 900;
		//輝度抽出用のシェーダーのファイルパスを指定する
		finalSpriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";
		//ピクセルシェーダーのエントリーポイントを指定する
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";
		//加算合成で描画するのでアルファブレンディングモードを加算にする
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		//描き込むレンダリングターゲットのフォーマットを指定する
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		
		//作成した初期化情報をもとにスプライトを初期化する
		finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::InitSprite(RenderTarget& renderTarget)
	{
		//最終合成後のテクスチャ
		SpriteInitData spriteInitData;
		spriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;
		//画像描画用のシェーダーのファイルパスを指定する
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		//作成した初期化情報をもとにスプライトを初期化する
		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void Bloom::BlurBeforeRender(RenderContext& renderContext)
	{
		//輝度抽出用のレンダリングターゲットに変更
		renderContext.WaitUntilToPossibleSetRenderTarget(luminanceRenderTarget);
		//レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(luminanceRenderTarget);
		//レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(luminanceRenderTarget);
		//輝度抽出を行う
		luminanceSprite.Draw(renderContext);
		//レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTarget(luminanceRenderTarget);
	}

	void Bloom::Blur(RenderContext& renderContext)
	{
		//ガウシアンブラーを4回実行する
		gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
		gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
		gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
		gaussianBlur[3].ExecuteOnGPU(renderContext, 10);
	}

	void Bloom::BlurAfterRender(RenderContext& renderContext, RenderTarget& renderTarget)
	{
		//レンダリングターゲットとして利用できるまで待つ
		renderContext.WaitUntilToPossibleSetRenderTarget(renderTarget);
		//レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(renderTarget);
		//最終合成
		finalSprite.Draw(renderContext);
		//レンダリングターゲットへの書き込み終了待ち
		renderContext.WaitUntilFinishDrawingToRenderTarget(renderTarget);
		//メインレンダリングターゲットの絵をフレームバッファーにコピー
		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		copyToFrameBufferSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		//ブラーを行ったテクスチャを描画
		copyToFrameBufferSprite.Draw(renderContext);
	}
}