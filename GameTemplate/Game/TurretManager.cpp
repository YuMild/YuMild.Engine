#include "stdafx.h"
#include "TurretManager.h"

#include "Energy.h"
#include "LeftWindow.h"
#include "LeftWindowDelete.h"

#include "NormalTurret.h"
#include "DualGunTurret.h"
#include "LaserTurret.h"
#include "RocketTurret.h"
#include "GenerationTurret.h"
#include "HealTurret.h"
#include "TeslaTurret.h"

namespace
{
	//�^���b�g�̐��Y�R�X�g
	float COST_NORMALTURRET = 100.0f;
	float COST_DUALGUNTURRET = 100.0f;
	float COST_LASERTURRET = 100.0f;
	float COST_ROCKETTURRET = 100.0f;
	float COST_GENERATIONTURRET = 100.0f;
	float COST_HEALTURRET = 100.0f;

	//Delete
	float DELETE_SPRITE_SIZE_WIDTH = 1280.0f;
	float DELETE_SPRITE_SIZE_HEIGHT = 720.0f;

	//�^���b�g�̈ړ��Ԋu
	float TURRET_POSITION_MOVE_NUM = 393.0f;

	//�J�[�\��
	Vector3 CURSOR_POSITION = { 200.0f,0.0f,190.0f };
}

bool TurretManager::Start()
{
	//FindGO
	m_energy = FindGO<Energy>("energy");
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	//�J�[�\���|�W�V�������f�t�H���g�l�ɐݒ�
	m_cursorPosition = CURSOR_POSITION;

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

	//Delete�E�B���h�E
	m_deleteWindow.Init("Assets/sprite/LeftWindow/Delete_Window.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteWindow.SetPosition({ 0.0f,0.0f,0.0f });
	m_deleteWindow.SetScale({ 1.0f,1.0f,1.0f });
	m_deleteWindow.Update();
	m_deleteDelete.Init("Assets/sprite/LeftWindow/Delete_Delete.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteDelete.SetPosition({ 0.0f,0.0f,0.0f });
	m_deleteDelete.SetScale({ 1.0f,1.0f,1.0f });
	m_deleteDelete.Update();
	m_deleteDeleteChoice.Init("Assets/sprite/LeftWindow/Delete_DeleteChoice.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteDeleteChoice.SetPosition({ 0.0f,0.0f,0.0f });
	m_deleteDeleteChoice.SetScale({ 1.0f,1.0f,1.0f });
	m_deleteDeleteChoice.Update();
	m_deleteCancel.Init("Assets/sprite/LeftWindow/Delete_Cancel.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteCancel.SetPosition({ 0.0f,0.0f,0.0f });
	m_deleteCancel.SetScale({ 1.0f,1.0f,1.0f });
	m_deleteCancel.Update();
	m_deleteCancelChoice.Init("Assets/sprite/LeftWindow/Delete_CancelChoice.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteCancelChoice.SetPosition({ 0.0f,0.0f,0.0f });
	m_deleteCancelChoice.SetScale({ 1.0f,1.0f,1.0f });
	m_deleteCancelChoice.Update();

	//�폜�p�̉摜�𐶐�
	for (int i = 0; i < 12; i++)
	{
		m_leftWindowDelete[i] = NewGO<LeftWindowDelete>(0, "leftWindowDelete");
		m_leftWindowDelete[i]->Init(enInitDeleteTurretSprite_Null); 
		m_leftWindowDelete[i]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	}

	//�G�t�F�N�g�̍쐬
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/CursorAfter.efk");

	//�����̍쐬
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/CursorAfter3.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/SetTurret.wav");

	return true;
}

void TurretManager::Init(TurretType enturret)
{
	//�X�V�������J�n
	m_isModelNewGO = true;
	m_isGorstModelNewGO = true;

	//������
	m_cursorPosition = CURSOR_POSITION;
	m_rotation = 0.0f;

	//�쐬����^���b�g�̎�ނ�����
	m_turretType = enturret;
}

void TurretManager::StateManager()
{
	/// <summary>
	/// NormalTurret
	/// </summary>
	if (m_turretType == enTurret_NormalTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_normalTurret = NewGO<NormalTurret>(0, "turret");
			m_normalTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_normalTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_normalTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_normalTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_normalTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_normalTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_normalTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_normalTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_normalTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_normalTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_normalTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_normalTurret);
			MakeNormalTurret();
			m_energy->SubEnergy(COST_DUALGUNTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_normalTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// DualGunTurret
	/// </summary>
	if (m_turretType == enTurret_DualGunTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_dualGunTurret = NewGO<DualGunTurret>(0, "turret");
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_dualGunTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_dualGunTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_dualGunTurret);
			MakeDualGunTurret();
			m_energy->SubEnergy(COST_DUALGUNTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_dualGunTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// LaserTurret
	/// </summary>
	else if (m_turretType == enTurret_LaserTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_laserTurret = NewGO<LaserTurret>(0, "turret");
			m_laserTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_laserTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_laserTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_laserTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_laserTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_laserTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_laserTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_laserTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_laserTurret);
			MakeLaserTurret();
			m_energy->SubEnergy(COST_LASERTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_dualGunTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// RocketTurret
	/// </summary>
	else if (m_turretType == enTurret_RocketTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_rocketTurret = NewGO<RocketTurret>(0, "turret");
			m_rocketTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_rocketTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_rocketTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_rocketTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_rocketTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_rocketTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_rocketTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_rocketTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_rocketTurret);
			MakeRocketTurret();
			m_energy->SubEnergy(COST_ROCKETTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_dualGunTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// GenerationTurret
	/// </summary>
	else if (m_turretType == enTurret_GenerationTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_generationTurret = NewGO<GenerationTurret>(0, "turret");
			m_generationTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_generationTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_generationTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_generationTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_generationTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_generationTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_generationTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_generationTurret);
			MakeGenerationTurret();
			m_energy->SubEnergy(COST_GENERATIONTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_dualGunTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// HealTurret
	/// </summary>
	else if (m_turretType == enTurret_HealTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_healTurret = NewGO<HealTurret>(0, "turret");
			m_healTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_healTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_healTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_healTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_healTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_healTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_healTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_healTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_healTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_healTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_healTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_healTurret);
			MakeHealTurret();
			m_energy->SubEnergy(COST_HEALTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_healTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}/// <summary>
	/// TeslaTurret
	/// </summary>
	else if (m_turretType == enTurret_TeslaTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_teslaTurret = NewGO<TeslaTurret>(0, "turret");
			m_teslaTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//��{�^��(8�L�[)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_teslaTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_teslaTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(2�L�[)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_teslaTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_teslaTurret->SetModelPosition(m_cursorPosition);
		}

		//�E�{�^��(6�L�[)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_teslaTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_teslaTurret->SetModelPosition(m_cursorPosition);
		}

		//���{�^��(4�L�[)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//�ғ��͈͓��Ȃ�
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_teslaTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_teslaTurret->SetModelPosition(m_cursorPosition);
		}

		//R�{�^��(L�L�[)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_teslaTurret->ModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//L�{�^��(I�L�[)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_teslaTurret->ModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//A�{�^��(J�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_teslaTurret);
			MakeTeslaTurret();
			m_energy->SubEnergy(COST_HEALTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//B�{�^��(K�L�[)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_healTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
}

void TurretManager::DeleteTurret()
{
	//�폜�m�F��ʂ̎�
	if (m_leftWindow->GetOperationState() == enOperationState_DeleteCheck_LeftWindow)
	{
		if (m_deleteSpriteScale <= 0.05f)
		{
			m_deleteSpriteScale += 0.01f;
		}
		else if (m_deleteSpriteScale >= 0.05f && m_deleteSpriteScale < 1.0f)
		{
			m_deleteSpriteScale += 0.1f;
		}
	}
	
	//�^���b�g�����݂��Ă���ӏ���I�����Ă����Ԃ�Select
	if (m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true && m_leftWindowDelete[m_leftWindow->GetSelectTurretNumber()]->GetIsDraw() == true)
	{
		m_turretDeleteState = enDeleteState_Cancel;
		m_leftWindow->SetOperationState(enOperationState_DeleteCheck_LeftWindow);
		m_leftWindow->SoundPlayWindow();
		m_deleteSpriteScale = 0.0f;
	}

	//Delete�m�F�E�B���h�E��Cancel���I������Ă��鎞�ɉE�L�[
	else if (m_turretDeleteState == enDeleteState_Cancel && g_pad[0]->IsTrigger(enButtonRight))
	{
		m_turretDeleteState = enDeleteState_Delete;
		m_leftWindow->SoundPlayChoice();
	}

	//Delete�m�F�E�B���h�E��Cancel���I������Ă��鎞��Select
	else if (m_turretDeleteState == enDeleteState_Cancel && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
	{
		m_turretDeleteState = enDeleteState_Null;
		m_leftWindow->SetOperationState(enOperationState_Delete_LeftWindow);
		m_leftWindow->SoundPlayWindow();
		m_deleteSpriteScale = 0.0f;
	}

	//Delete�m�F�E�B���h�E��Delete���I������Ă��鎞�ɍ��L�[
	else if (m_turretDeleteState == enDeleteState_Delete && g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_turretDeleteState = enDeleteState_Cancel;
		m_leftWindow->SoundPlayChoice();
	}

	//Delete�m�F�E�B���h�E��Delete���I������Ă��鎞��Select
	else if (m_turretDeleteState == enDeleteState_Delete && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
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
			//�폜�����^���b�g�ȍ~�̃^���b�g�̉摜�������ւ���
			for (int i = m_leftWindow->GetSelectTurretNumber(); i < m_turretsSum - 1; i++)
			{
				m_leftWindowDelete[i]->Init(m_leftWindowDelete[i + 1]->GetTurretType());
			}
			m_leftWindowDelete[m_turretsSum - 1]->SetIsDraw(false);
			m_turretsSum--;

			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
			SoundPlaySetTurret();
			m_turretDeleteState = enDeleteState_Null;
		}
	}

	m_deleteWindow.SetScale({ m_deleteSpriteScale,1.0f,1.0f });
	m_deleteWindow.Update();
}

void TurretManager::MakeNormalTurret()
{
	auto* turret = NewGO<NormalTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_NormalTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeDualGunTurret()
{
	auto* turret = NewGO<DualGunTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_DualGunTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeLaserTurret()
{
	auto* turret = NewGO<LaserTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_LaserTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeRocketTurret()
{
	auto* turret = NewGO<RocketTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_RocketTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeGenerationTurret()
{
	auto* turret = NewGO<GenerationTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_GenerationTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeHealTurret()
{
	auto* turret = NewGO<HealTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enTurret_HealTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::MakeTeslaTurret()
{
	auto* turret = NewGO<TeslaTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enTurret_TeslaTurret);
	m_leftWindowDelete[m_turretsSum]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	m_turretsSum++;
	m_isModelNewGO = false;
}

void TurretManager::Update()
{
	DeleteTurret();

	if (m_isModelNewGO)
	{
		StateManager();
	}
}

void TurretManager::Render(RenderContext& renderContext)
{
	if (m_turretDeleteState == enDeleteState_Cancel)
	{
		m_deleteWindow.Draw(renderContext);
		if (m_deleteSpriteScale >= 0.7f)
		{
			m_deleteDelete.Draw(renderContext);
			m_deleteCancel.Draw(renderContext);
			m_deleteCancelChoice.Draw(renderContext);
		}
	}

	if (m_turretDeleteState == enDeleteState_Delete)
	{
		m_deleteWindow.Draw(renderContext);
		if (m_deleteSpriteScale >= 0.7f)
		{	
			m_deleteDelete.Draw(renderContext);
			m_deleteDeleteChoice.Draw(renderContext);
			m_deleteCancel.Draw(renderContext);
		}
	}
}