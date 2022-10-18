#include "stdafx.h"
#include "Game.h"

#include "DualGunTurret.h"

namespace
{
	Vector3 STAGE_FIRST_POSITION = { 0.0f,0.0f,0.0f };
	Vector3 STAGE_FIRST_SCALE = { 1.0f,1.0f,1.0f };

	float PLAYER_COLLISION_SIZE_X = 20.0f;
	float PLAYER_COLLISION_SIZE_Y = 100.0f;

	float TURRET_POSITION_MOVE_NUM = 393.0f;
}

bool Game::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_stageModelRender.Init("Assets/ModelData/Stage/Stage.tkm", 3);
	m_stageModelRender.SetPosition(STAGE_FIRST_POSITION);
	m_stageModelRender.SetScale(STAGE_FIRST_SCALE);
	m_stageModelRender.Update();

	m_gridModelRender.Init("Assets/ModelData/Stage/Grid.tkm", 3);
	m_gridModelRender.SetPosition(STAGE_FIRST_POSITION);
	m_gridModelRender.SetScale(STAGE_FIRST_SCALE);
	m_gridModelRender.Update();

	return true;
}

void Game::OperationNormal()
{
	//Startボタン(Enterキー)
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		//操作モードを変更
		m_operationState = 1;
		m_dualGunTurret = NewGO<DualGunTurret>(0, "dualGunTurret");
	}

	//Aボタン(Jキー)
	if (g_pad[0]->IsPress(enButtonA))
	{
		//カメラの高度を上げる
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y + 100.0f,g_camera3D->GetPosition().z });
	}

	//Bボタン(Kキー)
	if (g_pad[0]->IsPress(enButtonB))
	{
		//カメラの高度を下げる
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y - 100.0f,g_camera3D->GetPosition().z });
	}
}

void Game::OperationSetTurret()
{
	//上ボタン(8キー)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//稼働範囲内なら
		if (m_cursorPosition.z >= -9600.0f)
		{
			m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//下ボタン(2キー)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//稼働範囲内なら
		if (m_cursorPosition.z <= 0.0f)
		{
			m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//右ボタン(6キー)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//稼働範囲内なら
		if (m_cursorPosition.x >= -3200.0f)
		{
			m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//左ボタン(4キー)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//稼働範囲内なら
		if (m_cursorPosition.x <= 3200.0f)
		{
			m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//Startボタン(Enterキー)
	if (g_pad[0]->IsTrigger(enButtonSelect) && m_operationState == 1)
	{
		//操作モードを変更
		m_operationState = 0;
	}

	//Xボタン(Lボタン)
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		m_dualGunTurret->RotationTurnRight();
	}

	//Yボタン(Iボタン)
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_dualGunTurret->RotationTurnLeft();
	}

	//Aボタン(Jキー)
	if (g_pad[0]->IsPress(enButtonA))
	{
		//カメラの高度を上げる
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y + 100.0f,g_camera3D->GetPosition().z });
	}

	//Bボタン(Kキー)
	if (g_pad[0]->IsPress(enButtonB))
	{
		//カメラの高度を下げる
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y - 100.0f,g_camera3D->GetPosition().z });
	}
}

void Game::Update()
{
	if (m_operationState == 0)
	{
		OperationNormal();
	}
	if (m_operationState == 1)
	{
		OperationSetTurret();
	}
}

void Game::Render(RenderContext& renderContext)
{
	m_stageModelRender.Draw(renderContext);
	if (m_operationState == 1)
	{
		m_gridModelRender.Draw(renderContext);
	}
}