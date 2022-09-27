#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });
	
	//ライト
	g_sceneLight.SetEyePosition({ g_camera3D->GetPosition().x, g_camera3D->GetPosition().y, g_camera3D->GetPosition().z });
	g_sceneLight.SetDirectionColor({ 1.0f,1.0f,1.0f });
	g_sceneLight.SetAmbientLight({ 5.0f,5.0f,5.0f });

	//ブルーム
	//g_bloom.InitBloom();

	//RenderTarget.Create()を利用してレンダリングターゲットを作成する
	RenderTarget mainRenderTarget;
	mainRenderTarget.Create(
		1600,                           //テクスチャの幅
		900,                            //テクスチャの長さ
		1,                              //Mipmapレベル
		1,                              //テクスチャ配列のサイズ
		DXGI_FORMAT_R32G32B32A32_FLOAT, //カラーバッファーのフォーマット
		DXGI_FORMAT_D32_FLOAT           //デプステンシルバッファーのフォーマット
	);

	g_bloom.InitRenderTarget();
	g_bloom.InitLuminanceSprite(mainRenderTarget);
	g_bloom.InitBlurSprite();
	g_bloom.InitFinalSprite();
	g_bloom.InitSprite(mainRenderTarget);

	NewGO<Game>(0, "game");

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();
		
		// レンダリングターゲットとして利用できるまで待つ
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// レンダリングターゲットを設定
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		// レンダリングターゲットをクリア
		renderContext.ClearRenderTargetView(mainRenderTarget);

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_k2EngineLow->ExecuteRender();

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		//ブラー前のレンダー
		g_bloom.BlurBeforeRender(renderContext);

		//ガウシアンブラーを実行
		g_bloom.Blur(renderContext);

		//ブラー後のレンダー
		g_bloom.BlurAfterRender(renderContext,mainRenderTarget);

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}