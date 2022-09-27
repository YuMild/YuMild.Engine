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
}