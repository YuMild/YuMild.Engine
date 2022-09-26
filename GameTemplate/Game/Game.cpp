#include "stdafx.h"
#include "Game.h"

bool Game::Start()
{
	m_modelRender.Init("Assets/modelData/teapot.tkm");
	m_modelRender.SetPosition({ 0.0f,0.0f,0.0f });

	return true;
}

void Game::Update()
{
	m_num += g_gameTime->GetFrameDeltaTime() * 10.0f;

	//g_sceneLight.SetDirectionColor({ m_num,m_num,m_num });
	//g_sceneLight.SetDirectionColor({ 1.0f,1.0f,1.0f });
	//g_sceneLight.SetAmbientLight({ m_num,m_num,m_num });

	m_pointLightPosition.x -= g_pad[0]->GetLStickXF();
	
	if (g_pad[0]->IsPress(enButtonB))
	{
		m_pointLightPosition.y += 1.0f;
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
		m_pointLightPosition.z -= 1.0f;
	}

	g_sceneLight.SetPointLightPosition(m_pointLightPosition);
}

void Game::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}