#include "stdafx.h"
#include "GameCamera.h"

namespace
{
	
}

bool GameCamera::Start()
{
	m_cameraPosition_X = 0.0f;
	m_cameraPosition_Y = 1500.0f;
	m_cameraPosition_Z = 1500.0f;
	g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	g_camera3D->SetFar(1000000000.0f);

	//フォント
	m_fontRenderCameraState.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderCameraState.SetScale(1.0f);
	m_fontRenderCameraState.SetPivot(1.0f, 0.5f);
	m_fontRenderCameraState.SetPosition({ 370.0,0.0f,0.0f });

	m_fontRenderX.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderX.SetScale(1.0f);
	m_fontRenderX.SetPivot(1.0f, 0.5f);
	m_fontRenderX.SetPosition({ 370.0,50.0f,0.0f });

	m_fontRenderY.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderY.SetScale(1.0f);
	m_fontRenderY.SetPivot(1.0f, 0.5f);
	m_fontRenderY.SetPosition({ 370.0,100.0f,0.0f });

	m_fontRenderZ.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderZ.SetScale(1.0f);
	m_fontRenderZ.SetPivot(1.0f, 0.5f);
	m_fontRenderZ.SetPosition({ 370.0,150.0f,0.0f });

	return true;
}

void GameCamera::Update()
{
	//カメラの視点と注視点の初期化
	if (m_cameraState == enCameraState_Normal)
	{
		//X
		if (m_cameraPosition_X < 0.0f)
		{
			m_cameraPosition_X += 25.0f;
		}
		else if (m_cameraPosition_X > 0.0f)
		{
			m_cameraPosition_X -= 25.0f;
		}
		//Y
		if (m_cameraPosition_Y < 1500.0f)
		{
			m_cameraPosition_Y += 250.0f;
		}
		else if (m_cameraPosition_Y > 1500.0f)
		{
			m_cameraPosition_Y -= 250.0f;
		}
		//Z
		if (m_cameraPosition_Z < 1500.0f)
		{
			m_cameraPosition_Z += 25.0f;
		}
		else if (m_cameraPosition_Z > 1500.0f)
		{
			m_cameraPosition_Z -= 25.0f;
		}

		g_camera3D->SetTarget({ 0.0f,0.0f,-1000.0f });
		g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	}
	else if (m_cameraState == enCameraState_SetTurret)
	{
		//X
		if (m_cameraPosition_X < 0.0f)
		{
			m_cameraPosition_X += 25.0f;
		}
		else if (m_cameraPosition_X > 0.0f)
		{
			m_cameraPosition_X -= 25.0f;
		}
		//Y
		if (m_cameraPosition_Y < 5500.0f)
		{
			m_cameraPosition_Y += 250.0f;
		}
		else if (m_cameraPosition_Y > 5500.0f)
		{
			m_cameraPosition_Y -= 250.0f;
		}
		//Z
		if (m_cameraPosition_Z < 1000.0f)
		{
			m_cameraPosition_Z += 25.0f;
		}
		else if (m_cameraPosition_Z > 1000.0f)
		{
			m_cameraPosition_Z -= 25.0f;
		}

		g_camera3D->SetTarget({ 0.0f,0.0f,-2500.0f });
		g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	}
	else if (m_cameraState == enCameraState_SpaceShip)
	{
		//X
		if (m_cameraPosition_X < 0.0f)
		{
			m_cameraPosition_X += 10.0f;
		}
		else if (m_cameraPosition_X > 0.0f)
		{
			m_cameraPosition_X -= 10.0f;
		}
		//Y
		if (m_cameraPosition_Y < 1000.0f)
		{
			m_cameraPosition_Y += 10.0f;
		}
		else if (m_cameraPosition_Y > 1000.0f)
		{
			m_cameraPosition_Y -= 10.0f;
		}
		//Z
		if (m_cameraPosition_Z < 1500.0f)
		{
			m_cameraPosition_Z += 10.0f;
		}
		else if (m_cameraPosition_Z > 1500.0f)
		{
			m_cameraPosition_Z -= 10.0f;
		}

		g_camera3D->SetTarget({ 0.0f,0.0f,-1000.0f });
		g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	}

	wchar_t G[256];
	swprintf_s(G, 256, L"%04d", int(m_cameraState));
	m_fontRenderCameraState.SetText(G);
	wchar_t X[256];
	swprintf_s(X, 256, L"%04d", int(m_cameraPosition_X));
	m_fontRenderX.SetText(X);
	wchar_t Y[256];
	swprintf_s(Y, 256, L"%04d", int(m_cameraPosition_Y));
	m_fontRenderY.SetText(Y);
	wchar_t Z[256];
	swprintf_s(Z, 256, L"%04d", int(m_cameraPosition_Z));
	m_fontRenderZ.SetText(Z);
}

void GameCamera::Render(RenderContext& renderContext)
{
	m_fontRenderCameraState.Draw(renderContext);
	m_fontRenderX.Draw(renderContext);
	m_fontRenderY.Draw(renderContext);
	m_fontRenderZ.Draw(renderContext);
}