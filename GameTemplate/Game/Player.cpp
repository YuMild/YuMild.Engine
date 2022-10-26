#include "stdafx.h"
#include "Player.h"

#include "LeftWindow.h"

namespace
{
	Vector3 STAGE_FIRST_POSITION = { 0.0f,0.0f,0.0f };
	Vector3 STAGE_FIRST_SCALE = { 1.0f,1.0f,1.0f };

	float TURRET_POSITION_MOVE_NUM = 393.0f;
}

bool Player::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	m_gridModelRender.Init("Assets/ModelData/Stage/Grid.tkm", ShadowRecieveAndDrop);
	m_gridModelRender.SetPosition(STAGE_FIRST_POSITION);
	m_gridModelRender.SetScale(STAGE_FIRST_SCALE);
	m_gridModelRender.Update();

	return true;
}

void Player::OperationNormal()
{
	//Startボタン(Enterキー)
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		//操作モードを変更
		m_operationState = enOparationStateSelectTurret;
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

void Player::OperationSelectTurret()
{
	//上ボタン(8キー)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		m_leftWindow->TurretCursorUp();
	}

	//下ボタン(2キー)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		m_leftWindow->TurretCursorDown();
	}

	//右ボタン(6キー)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		m_leftWindow->TurretCursorRight();
	}

	//左ボタン(4キー)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_leftWindow->TurretCursorLeft();
	}

	//Startボタン(Enterキー)
	if (g_pad[0]->IsTrigger(enButtonStart) && m_operationState == enOparationStateSelectTurret)
	{
		//if (m_leftWindow->GetSelectTurretNumber() == enTurretDualGunTurret)
		//{
			m_dualGunTurret = NewGO<DualGunTurret>(0, "dualGunTurret");
		//}
		//操作モードを変更
		m_operationState = enOparationStateSetTurret;
	}
}

void Player::OperationSetTurret()
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
	if (g_pad[0]->IsTrigger(enButtonStart) && m_operationState == enOparationStateSetTurret)
	{
		//操作モードを変更
		m_operationState = enOparationStateNormal;
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

void Player::Update()
{
	if (m_operationState == enOparationStateNormal)
	{
		OperationNormal();
	}
	else if (m_operationState == enOparationStateSelectTurret)
	{
		OperationSelectTurret();
	}
	else if (m_operationState == enOparationStateSetTurret)
	{
		OperationSetTurret();
	}
}

void Player::Render(RenderContext& renderContext)
{
	if (m_operationState == enOparationStateSetTurret)
	{
		m_gridModelRender.Draw(renderContext);
	}
}