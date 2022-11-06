#include "stdafx.h"
#include "TurretManager.h"

#include "LeftWindow.h"

#include "DualGunTurret.h"
#include "LaserTurret.h"
#include "RocketTurret.h"

namespace
{
	float TURRET_POSITION_MOVE_NUM = 393.0f;
	Vector3 FIRST_CURSOR_POSITION = { 200.0f,0.0f,190.0f };
}

bool TurretManager::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	m_cursorPosition = FIRST_CURSOR_POSITION;

	return true;
}

void TurretManager::Init(Turret enturret)
{
	//更新処理を開始
	m_isModelNewGO = true;
	m_isGorstModelNewGO = true;

	//初期化
	m_cursorPosition = FIRST_CURSOR_POSITION;
	m_rotation = 0.0f;

	//作成するタレットの種類を決定
	m_turretType = enturret;
}

void TurretManager::StateManager()
{
	switch (m_turretType)
	{
	case enTurret_DualGunTurret:

		if (m_isGorstModelNewGO)
		{
			m_dualGunTurret= NewGO<DualGunTurret>(0, "dualGunTurret");
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//Xボタン(Lボタン)
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_dualGunTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
		}

		//Yボタン(Iボタン)
		if (g_pad[0]->IsTrigger(enButtonY))
		{
			m_dualGunTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
		}

		//Startボタン(Enterキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect))
		{
			DeleteGO(m_dualGunTurret);
			MakeDualGunTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	case enTurret_LaserTurret:

		if (m_isGorstModelNewGO)
		{
			m_laserTurret = NewGO<LaserTurret>(0, "laserTurret");
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//Xボタン(Lボタン)
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_laserTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
		}

		//Yボタン(Iボタン)
		if (g_pad[0]->IsTrigger(enButtonY))
		{
			m_laserTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
		}

		//Startボタン(Enterキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect))
		{
			DeleteGO(m_laserTurret);
			MakeLaserTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	case enTurret_RocketTurret:

		if (m_isGorstModelNewGO)
		{
			m_rocketTurret = NewGO<RocketTurret>(0, "rocketTurret");
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//Xボタン(Lボタン)
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_rocketTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
		}

		//Yボタン(Iボタン)
		if (g_pad[0]->IsTrigger(enButtonY))
		{
			m_rocketTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
		}

		//Startボタン(Enterキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect))
		{
			DeleteGO(m_rocketTurret);
			MakeRocketTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	default:

		break;
	}
}

void TurretManager::MakeDualGunTurret()
{
	auto* turret = NewGO<DualGunTurret>(0, "dualGunTurret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	m_turrets.push_back(turret);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeLaserTurret()
{
	auto* turret = NewGO<LaserTurret>(0, "laserTurret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	m_turrets.push_back(turret);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeRocketTurret()
{
	auto* turret = NewGO<RocketTurret>(0, "rocketTurret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	m_turrets.push_back(turret);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::Update()
{
	if (m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect) && m_turretsSum != 0)
	{
		std::vector<IGameObject*>::iterator it;
		//要素を探す
		it = std::find(
			m_turrets.begin(),
			m_turrets.end(),
			m_turrets[m_leftWindow->GetSelectTurretNumber()]
		);
		//要素が見つかったら
		if (it != m_turrets.end())
		{
			//削除する
			DeleteGO(m_turrets[m_leftWindow->GetSelectTurretNumber()]);
			m_turrets.erase(it);
			m_turretsSum--;
		}
	}

	if (m_isModelNewGO)
	{
		StateManager();
	}
}