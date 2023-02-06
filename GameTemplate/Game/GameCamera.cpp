#include "stdafx.h"
#include "GameCamera.h"

#include "stdlib.h"

namespace
{
	//ターゲット
	const float CAMERATARGET_NORMAL_Z		= -1000.0f;
	const float CAMERATARGET_SETTURRET_Z	= -2500.0f;
	const float CAMERATARGET_SPACESHIP_Z	= -1000.0f;
	//ポジション
	const float CAMERAPOSITION_NORMAL_X		= 0.0f;
	const float CAMERAPOSITION_NORMAL_Y		= 1500.0f;
	const float CAMERAPOSITION_NORMAL_Z		= 1500.0f;
	const float CAMERAPOSITION_SETTURRET_X	= 0.0f;
	const float CAMERAPOSITION_SETTURRET_Y	= 5500.0f;
	const float CAMERAPOSITION_SETTURRET_Z	= 1000.0f;
	const float CAMERAPOSITION_SPACESHIP_X	= 0.0f;
	const float CAMERAPOSITION_SPACESHIP_Y	= 900.0f;
	const float CAMERAPOSITION_SPACESHIP_Z	= 1500.0f;
}

bool GameCamera::Start()
{
	m_cameraTarget_Z = CAMERATARGET_NORMAL_Z;
	g_camera3D->SetTarget({ 0.0f,0.0f,m_cameraTarget_Z });
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
	/// <summary>
	/// Normal
	/// </summary>
	if (m_cameraState == enCameraState_Normal && m_cameraShake == false)
	{
		//Target
		if (m_cameraTarget_Z > CAMERATARGET_NORMAL_Z)
		{
			m_cameraTarget_Z -= 100.0f;
		}
		else if (m_cameraTarget_Z < CAMERATARGET_NORMAL_Z)
		{
			m_cameraTarget_Z += 100.0f;
		}
		//X
		if (m_cameraPosition_X < CAMERAPOSITION_NORMAL_X)
		{
			m_cameraPosition_X += 25.0f;
		}
		else if (m_cameraPosition_X > CAMERAPOSITION_NORMAL_X)
		{
			m_cameraPosition_X -= 25.0f;
		}
		//Y
		if (m_cameraPosition_Y < CAMERAPOSITION_NORMAL_Y)
		{
			m_cameraPosition_Y += 200.0f;
		}
		else if (m_cameraPosition_Y > CAMERAPOSITION_NORMAL_Y)
		{
			m_cameraPosition_Y -= 200.0f;
		}
		//Z
		if (m_cameraPosition_Z < CAMERAPOSITION_NORMAL_Z)
		{
			m_cameraPosition_Z += 25.0f;
		}
		else if (m_cameraPosition_Z > CAMERAPOSITION_NORMAL_Z)
		{
			m_cameraPosition_Z -= 25.0f;
		}

		g_camera3D->SetTarget({ 0.0f,0.0f,m_cameraTarget_Z });
		g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	}
	/// <summary>
	/// SetTurret
	/// </summary>
	if (m_cameraState == enCameraState_SetTurret && m_cameraShake == false)
	{
		//Target
		if (m_cameraTarget_Z > CAMERATARGET_SETTURRET_Z)
		{
			m_cameraTarget_Z -= 100.0f;
		}
		else if (m_cameraTarget_Z < CAMERATARGET_SETTURRET_Z)
		{
			m_cameraTarget_Z += 100.0f;
		}
		//X
		if (m_cameraPosition_X < CAMERAPOSITION_SETTURRET_X)
		{
			m_cameraPosition_X += 25.0f;
		}
		else if (m_cameraPosition_X > CAMERAPOSITION_SETTURRET_X)
		{
			m_cameraPosition_X -= 25.0f;
		}
		//Y
		if (m_cameraPosition_Y < CAMERAPOSITION_SETTURRET_Y)
		{
			m_cameraPosition_Y += 200.0f;
		}
		else if (m_cameraPosition_Y > CAMERAPOSITION_SETTURRET_Y)
		{
			m_cameraPosition_Y -= 200.0f;
		}
		//Z
		if (m_cameraPosition_Z < CAMERAPOSITION_SETTURRET_Z)
		{
			m_cameraPosition_Z += 25.0f;
		}
		else if (m_cameraPosition_Z > CAMERAPOSITION_SETTURRET_Z)
		{
			m_cameraPosition_Z -= 25.0f;
		}

		g_camera3D->SetTarget({ 0.0f,0.0f,m_cameraTarget_Z });
		g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	}
	/// <summary>
	/// SpaceShip
	/// </summary>
	if (m_cameraState == enCameraState_SpaceShip && m_cameraShake == false)
	{
		//Target
		if (m_cameraTarget_Z > CAMERATARGET_SPACESHIP_Z)
		{
			m_cameraTarget_Z -= 100.0f;
		}
		else if (m_cameraTarget_Z < CAMERATARGET_SPACESHIP_Z)
		{
			m_cameraTarget_Z += 100.0f;
		}
		//カメラが高過ぎたら一旦通常時まで落とす
		if (m_cameraPosition_Y >= 1500.0f)
		{
			m_cameraPosition_Y = 1500.0f;
			m_cameraTarget_Z = 1000.0f;
		}
		//X
		if (m_cameraPosition_X < CAMERAPOSITION_SPACESHIP_X)
		{
			m_cameraPosition_X += 25.0f;
		}
		else if (m_cameraPosition_X > CAMERAPOSITION_SPACESHIP_X)
		{
			m_cameraPosition_X -= 25.0f;
		}
		//Y
		if (m_cameraPosition_Y < CAMERAPOSITION_SPACESHIP_Y)
		{
			m_cameraPosition_Y += 10.0f;
		}
		else if (m_cameraPosition_Y > CAMERAPOSITION_SPACESHIP_Y)
		{
			m_cameraPosition_Y -= 10.0f;
		}
		//Z
		if (m_cameraPosition_Z < CAMERAPOSITION_SPACESHIP_Z)
		{
			m_cameraPosition_Z += 25.0f;
		}
		else if (m_cameraPosition_Z > CAMERAPOSITION_SPACESHIP_Z)
		{
			m_cameraPosition_Z -= 25.0f;
		}

		g_camera3D->SetTarget({ 0.0f,0.0f,m_cameraTarget_Z });
		g_camera3D->SetPosition({ m_cameraPosition_X,m_cameraPosition_Y,m_cameraPosition_Z });
	}
	/// <summary>
	/// カメラの揺れ
	/// </summary>
	if (m_cameraShake == true)
	{
		m_shakeTimer += g_gameTime->GetFrameDeltaTime();
		if (m_shakeTimer > 0.0f && m_shakeTimer <= 0.05f)
		{
			g_camera3D->SetTarget({ 0.0f + rand() % 100 + 50,0.0f,m_cameraTarget_Z + rand() % 100 + 50 });
			g_camera3D->SetPosition({ m_cameraPosition_X - rand() % 100 + 50,m_cameraPosition_Y - rand() % 500 + 250,m_cameraPosition_Z });
		}
		else if (m_shakeTimer > 0.05f && m_shakeTimer <= 0.1f)
		{
			g_camera3D->SetTarget({ 0.0f + rand() % 250 + 100 ,0.0f,m_cameraTarget_Z + rand() % 250 + 100 });
			g_camera3D->SetPosition({ m_cameraPosition_X - rand() % 250 + 100,m_cameraPosition_Y - rand() % 1000 + 500,m_cameraPosition_Z });
		}
		else if (m_shakeTimer > 0.1f && m_shakeTimer <= 0.15f)
		{
			g_camera3D->SetTarget({ 0.0f - rand() % 100 + 50,0.0f,m_cameraTarget_Z - rand() % 100 + 50 });
			g_camera3D->SetPosition({ m_cameraPosition_X + rand() % 100 + 50,m_cameraPosition_Y + rand() % 500 + 250,m_cameraPosition_Z });
		}
		else if (m_shakeTimer > 0.15f && m_shakeTimer <= 0.2f)
		{
			g_camera3D->SetTarget({ 0.0f - rand() % 250 + 100,0.0f,m_cameraTarget_Z - rand() % 250 + 100 });
			g_camera3D->SetPosition({ m_cameraPosition_X + rand() % 250 + 100,m_cameraPosition_Y + rand() % 1000 + 500,m_cameraPosition_Z });
		}
		else if (m_shakeTimer > 0.2f && m_shakeTimer <= 0.25f)
		{
			g_camera3D->SetTarget({ 0.0f + rand() % 50 + 25,0.0f,m_cameraTarget_Z + rand() % 100 + 50 });
			g_camera3D->SetPosition({ m_cameraPosition_X - rand() % 50 + 25,m_cameraPosition_Y - rand() % 200 + 100,m_cameraPosition_Z });
		}
		else if (m_shakeTimer > 0.25f && m_shakeTimer <= 0.3f)
		{
			g_camera3D->SetTarget({ 0.0f - rand() % 50 + 25,0.0f,m_cameraTarget_Z - rand() % 100 + 50 });
			g_camera3D->SetPosition({ m_cameraPosition_X + rand() % 50 + 25,m_cameraPosition_Y + rand() % 200 + 100,m_cameraPosition_Z });
		}
		else if (m_shakeTimer > 0.3f)
		{
			m_shakeTimer = 0.0f;
			m_cameraShake = false;
		}
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
	//m_fontRenderCameraState.Draw(renderContext);
	//m_fontRenderX.Draw(renderContext);
	//m_fontRenderY.Draw(renderContext);
	//m_fontRenderZ.Draw(renderContext);
}