#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

#include "ModelRender.h"

namespace nsK2EngineLow
{
	ShadowMapRender g_shadowMapRender;

	void ShadowMapRender::Init()
	{
		m_lightCamera.SetPosition({ g_camera3D->GetTarget().x,g_camera3D->GetTarget().y + 500.0f,g_camera3D->GetTarget().z });
		m_lightCamera.SetTarget(g_camera3D->GetTarget());
		m_lightCamera.SetUp(1, 0, 0);
		m_lightCamera.Update();

		float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_shadowMap.Create(
			1024,
			1024,
			1,
			1,
			//【注目】シャドウマップのカラーバッファのフォーマットを変更している。
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}

	void ShadowMapRender::Render(RenderContext& renderContext)
	{
		renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
		renderContext.SetRenderTargetAndViewport(m_shadowMap);
		renderContext.ClearRenderTargetView(m_shadowMap);

		m_modelRender.ShadowMapDraw(renderContext, m_lightCamera);
		
		renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);
		
		renderContext.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
			);

		renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
	}
}