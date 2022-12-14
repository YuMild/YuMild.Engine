#include "stdafx.h"
#include "system/system.h"
#include "Title.h"

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
	
	//ライト
	g_sceneLight.SetEyePosition({ g_camera3D->GetPosition().x, g_camera3D->GetPosition().y, g_camera3D->GetPosition().z });
	g_sceneLight.SetDirectionColor({ 1.0f,1.0f,1.0f });

	//ポストエフェクト
	g_renderingEngine.Init();
	g_postEffect.Init();
	g_bloom.Init();

	//ゲームの作成
	NewGO<Title>(0, "title");

	/*Texture emmisionMap;
	emmisionMap.InitFromDDSFile(L"test.dds");
	ModelInitData modelInitData;
	modelInitData.m_expandShaderResoruceView[0] = &emmisionMap;
	*/

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();
		
		//ゲームオブジェクトマネージャーの更新処理
		g_k2EngineLow->ExecuteUpdate();

		//モデルの描画
		g_renderingEngine.Execute(renderContext);

		//ポストエフェクト
		g_postEffect.Render(renderContext);

		//デバッグ描画処理を実行
		g_k2EngineLow->DebubDrawWorld();

		//フレームの終了時に呼び出す必要がある処理を実行
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}