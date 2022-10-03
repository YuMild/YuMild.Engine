#include "stdafx.h"
#include "Game.h"

bool Game::Start()
{
	m_modelRender.Init("Assets/ModelData/unityChan.tkm");
	m_modelRender.SetPosition({ 0.0f,30.0f,0.0f });
	m_modelRender.Update();

	m_modelRenderReciever.InitShadowRecieverModel("Assets/modelData/bg/bg.tkm");
	m_modelRenderReciever.SetPosition({ 0.0f,0.0f,0.0f });
	m_modelRenderReciever.Update();

	return true;
}

void Game::Update()
{
	m_num += g_gameTime->GetFrameDeltaTime() * 10.0f;
	
	if (g_pad[0]->IsPress(enButtonB))
	{
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x - 10.0f,g_camera3D->GetPosition().y-10.0f,g_camera3D->GetPosition().z - 10.0f });
		g_camera3D->Update();
	}
	if (g_pad[0]->IsPress(enButtonX))
	{
		m_pointLightPosition.y -= 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonY))
	{
		m_pointLightPosition.z += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonA))
	{
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x + 10.0f,g_camera3D->GetPosition().y + 10.0f,g_camera3D->GetPosition().z + 10.0f });
		g_camera3D->Update();
	}

	g_sceneLight.SetPointLightPosition(m_pointLightPosition);
}

void Game::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
	m_modelRender.ShadowMapDraw(renderContext, g_shadowMapRender.GetLightCamera());
}