#include "stdafx.h"
#include "TurretManager.h"

#include "LeftWindow.h"
#include "LeftWindow_Delete.h"

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

	//�J�[�\���|�W�V�������f�t�H���g�l�ɐݒ�
	m_cursorPosition = FIRST_CURSOR_POSITION;

	//�폜�p�̉摜�̃|�W�V������ݒ�
	m_deleteSpritePosition[0] = { -500.0f,0.0f,0.0f };
	m_deleteSpritePosition[1] = { -415.0f,0.0f,0.0f };
	m_deleteSpritePosition[2] = { -330.0f,0.0f,0.0f };
	m_deleteSpritePosition[3] = { -245.0f,0.0f,0.0f };
	m_deleteSpritePosition[4] = { -500.0f,-100.0f,0.0f };
	m_deleteSpritePosition[5] = { -415.0f,-100.0f,0.0f };
	m_deleteSpritePosition[6] = { -330.0f,-100.0f,0.0f };
	m_deleteSpritePosition[7] = { -245.0f,-100.0f,0.0f };
	m_deleteSpritePosition[8] = { -500.0f,-200.0f,0.0f };
	m_deleteSpritePosition[9] = { -415.0f,-200.0f,0.0f };
	m_deleteSpritePosition[10] = { -330.0f,-200.0f,0.0f };
	m_deleteSpritePosition[11] = { -245.0f,-200.0f,0.0f };

	//�폜�p�̉摜�𐶐�
	for (int i = 0; i < 12; i++)
	{
		m_leftWindow_Delete[i] = NewGO<LeftWindow_Delete>(0, "leftWindow_Delete");
		m_leftWindow_Delete[i]->Init(enInitDeleteTurretSprite_Null); 
		m_leftWindow_Delete[i]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	}

	//�����̍쐬
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/SetTurret.wav");

	return true;
}

void TurretManager::Init(Turret enturret)
{
	//�X�V�������J�n
	m_isModelNewGO = true;
	m_isGorstModelNewGO = true;

	//������
	m_cursorPosition = FIRST_CURSOR_POSITION;
	m_rotation = 0.0f;

	//�쐬����^���b�g�̎�ނ�����
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

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//X�{�^��(L�{�^��)
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_dualGunTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
		}

		//Y�{�^��(I�{�^��)
		if (g_pad[0]->IsTrigger(enButtonY))
		{
			m_dualGunTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
		}

		//Start�{�^��(Enter�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect))
		{
			DeleteGO(m_dualGunTurret);
			MakeDualGunTurret();
			SoundPlaySetTurret();
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

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_laserTurret->Update();
		}

		//X�{�^��(L�{�^��)
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_laserTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
		}

		//Y�{�^��(I�{�^��)
		if (g_pad[0]->IsTrigger(enButtonY))
		{
			m_laserTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
		}

		//Start�{�^��(Enter�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect))
		{
			DeleteGO(m_laserTurret);
			MakeLaserTurret();
			SoundPlaySetTurret();
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

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_rocketTurret->Update();
		}

		//X�{�^��(L�{�^��)
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			m_rocketTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
		}

		//Y�{�^��(I�{�^��)
		if (g_pad[0]->IsTrigger(enButtonY))
		{
			m_rocketTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
		}

		//Start�{�^��(Enter�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect))
		{
			DeleteGO(m_rocketTurret);
			MakeRocketTurret();
			SoundPlaySetTurret();
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
	m_leftWindow_Delete[m_turretsSum]->Init(enInitDeleteTurretSprite_DualGunTurret);
	m_leftWindow_Delete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeLaserTurret()
{
	auto* turret = NewGO<LaserTurret>(0, "laserTurret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	m_turrets.push_back(turret);
	m_leftWindow_Delete[m_turretsSum]->Init(enInitDeleteTurretSprite_LaserTurret);
	m_leftWindow_Delete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeRocketTurret()
{
	auto* turret = NewGO<RocketTurret>(0, "rocketTurret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	m_turrets.push_back(turret);
	m_leftWindow_Delete[m_turretsSum]->Init(enInitDeleteTurretSprite_RocketTurret);
	m_leftWindow_Delete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::Update()
{
	if (m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow && g_pad[0]->IsTrigger(enButtonSelect) && m_turretsSum != 0)
	{
		std::vector<IGameObject*>::iterator it;
		//�v�f��T��
		it = std::find(
			m_turrets.begin(),
			m_turrets.end(),
			m_turrets[m_leftWindow->GetSelectTurretNumber()]
		);
		//�v�f������������
		if (it != m_turrets.end())
		{
			//�폜����
			DeleteGO(m_turrets[m_leftWindow->GetSelectTurretNumber()]);
			m_turrets.erase(it);
			for (int i = m_leftWindow->GetSelectTurretNumber(); i < m_turretsSum - 1; i++)
			{
				m_leftWindow_Delete[i]->Init(m_leftWindow_Delete[i + 1]->GetTurretType());
			}
			m_leftWindow_Delete[m_turretsSum - 1]->SetDraw(false);
			m_turretsSum--;
		}
	}

	if (m_isModelNewGO)
	{
		StateManager();
	}
}