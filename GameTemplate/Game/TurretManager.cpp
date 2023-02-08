#include "stdafx.h"
#include "TurretManager.h"

#include "Energy.h"
#include "Game.h"
#include "LeftWindow.h"
#include "LeftWindowDelete.h"

#include "NormalTurret.h"
#include "DualGunTurret.h"
#include "LaserTurret.h"
#include "RocketTurret.h"
#include "GeneratorTurret.h"
#include "HealTurret.h"
#include "TeslaTurret.h"
#include "HolyTurret.h"

namespace
{
	//Delete
	float		DELETE_SPRITE_SIZE_WIDTH	= 1280.0f;
	float		DELETE_SPRITE_SIZE_HEIGHT	= 720.0f;
	Vector3		DELETE_SPRITE_SIZE			= { 1.0f,1.0f,1.0f };
	Vector3		DELETE_SPRITE_POSITION		= { 0.0f,300.0f,0.0f };

	//タレットの移動間隔
	float		TURRET_POSITION_MOVE_NUM	= 393.0f;

	//カーソル
	Vector3		CURSOR_POSITION				= { 200.0f,0.0f,-2561.0f };
}

bool TurretManager::Start()
{
	//FindGO
	m_energy = FindGO<Energy>("energy");
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	//カーソルポジションをデフォルト値に設定
	m_cursorPosition = CURSOR_POSITION;

	//削除用の画像のポジションを設定
	m_deleteSpritePosition[0]	= { -500.0f,0.0f,0.0f };
	m_deleteSpritePosition[1]	= { -415.0f,0.0f,0.0f };
	m_deleteSpritePosition[2]	= { -330.0f,0.0f,0.0f };
	m_deleteSpritePosition[3]	= { -245.0f,0.0f,0.0f };
	m_deleteSpritePosition[4]	= { -500.0f,-100.0f,0.0f };
	m_deleteSpritePosition[5]	= { -415.0f,-100.0f,0.0f };
	m_deleteSpritePosition[6]	= { -330.0f,-100.0f,0.0f };
	m_deleteSpritePosition[7]	= { -245.0f,-100.0f,0.0f };
	m_deleteSpritePosition[8]	= { -500.0f,-200.0f,0.0f };
	m_deleteSpritePosition[9]	= { -415.0f,-200.0f,0.0f };
	m_deleteSpritePosition[10]	= { -330.0f,-200.0f,0.0f };
	m_deleteSpritePosition[11]	= { -245.0f,-200.0f,0.0f };

	//Deleteウィンドウ
	m_deleteWindow.Init("Assets/sprite/LeftWindow/Delete_Window.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteWindow.SetPosition(DELETE_SPRITE_POSITION);
	m_deleteWindow.SetScale(DELETE_SPRITE_SIZE);
	m_deleteWindow.Update();
	m_deleteDelete.Init("Assets/sprite/LeftWindow/Delete_Delete.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteDelete.SetPosition(DELETE_SPRITE_POSITION);
	m_deleteDelete.SetScale(DELETE_SPRITE_SIZE);
	m_deleteDelete.Update();
	m_deleteDeleteChoice.Init("Assets/sprite/LeftWindow/Delete_DeleteChoice.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteDeleteChoice.SetPosition(DELETE_SPRITE_POSITION);
	m_deleteDeleteChoice.SetScale(DELETE_SPRITE_SIZE);
	m_deleteDeleteChoice.Update();
	m_deleteCancel.Init("Assets/sprite/LeftWindow/Delete_Cancel.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteCancel.SetPosition(DELETE_SPRITE_POSITION);
	m_deleteCancel.SetScale(DELETE_SPRITE_SIZE);
	m_deleteCancel.Update();
	m_deleteCancelChoice.Init("Assets/sprite/LeftWindow/Delete_CancelChoice.dds", DELETE_SPRITE_SIZE_WIDTH, DELETE_SPRITE_SIZE_HEIGHT);
	m_deleteCancelChoice.SetPosition(DELETE_SPRITE_POSITION);
	m_deleteCancelChoice.SetScale(DELETE_SPRITE_SIZE);
	m_deleteCancelChoice.Update();

	//削除用の画像を生成
	for (int i = 0; i < 12; i++)
	{
		m_leftWindowDelete[i] = NewGO<LeftWindowDelete>(0, "leftWindowDelete");
		m_leftWindowDelete[i]->Init(enInitDeleteTurretSprite_Null); 
		m_leftWindowDelete[i]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	}

	//エフェクトの作成

	//音声の作成
	g_soundEngine->ResistWaveFileBank(enSoundNumber_SetTurret, "Assets/sound/SetTurret.wav");

	return true;
}

void TurretManager::Init(TurretType enturret)
{
	//更新処理を開始
	m_isModelNewGO = true;
	m_isGorstModelNewGO = true;

	//初期化
	m_cursorPosition = CURSOR_POSITION;
	m_rotation = 0.0f;

	//作成するタレットの種類を決定
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

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//稼働範囲内なら
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

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//稼働範囲内なら
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

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//稼働範囲内なら
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

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_normalTurret->GetModelPosition();
			//稼働範囲内なら
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

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_normalTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_normalTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_normalTurret);
			MakeNormalTurret();
			m_energy->SubEnergy(m_energy->COST_NORMALTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
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
	else if (m_turretType == enTurret_DualGunTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_dualGunTurret = NewGO<DualGunTurret>(0, "turret");
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
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

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
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

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
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

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_dualGunTurret->GetModelPosition();
			//稼働範囲内なら
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

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_dualGunTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_dualGunTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_dualGunTurret);
			MakeDualGunTurret();
			m_energy->SubEnergy(m_energy->COST_DUALGUNTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
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

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
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

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
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

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
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

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_laserTurret->GetModelPosition();
			//稼働範囲内なら
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

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB3))
		{
			m_laserTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB3))
		{
			m_laserTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_laserTurret);
			MakeLaserTurret();
			m_energy->SubEnergy(m_energy->COST_LASERTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
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

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
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

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
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

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
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

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_rocketTurret->GetModelPosition();
			//稼働範囲内なら
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

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_rocketTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_rocketTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_rocketTurret);
			MakeRocketTurret();
			m_energy->SubEnergy(m_energy->COST_ROCKETTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_dualGunTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// GeneratorTurret
	/// </summary>
	else if (m_turretType == enTurret_GeneratorTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_generatorTurret = NewGO<GeneratorTurret>(0, "turret");
			m_generatorTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_generatorTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_generatorTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generatorTurret->SetModelPosition(m_cursorPosition);
		}

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_generatorTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_generatorTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generatorTurret->SetModelPosition(m_cursorPosition);
		}

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_generatorTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_generatorTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generatorTurret->SetModelPosition(m_cursorPosition);
		}

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_generatorTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_generatorTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_generatorTurret->SetModelPosition(m_cursorPosition);
		}

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_generatorTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_generatorTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_generatorTurret);
			MakeGeneratorTurret();
			m_energy->SubEnergy(m_energy->COST_GENERATIONTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
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

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//稼働範囲内なら
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

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//稼働範囲内なら
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

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//稼働範囲内なら
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

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_healTurret->GetModelPosition();
			//稼働範囲内なら
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

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_healTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_healTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_healTurret);
			MakeHealTurret();
			m_energy->SubEnergy(m_energy->COST_HEALTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_healTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}/// <summary>
	/// <summary>
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

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//稼働範囲内なら
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

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//稼働範囲内なら
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

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//稼働範囲内なら
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

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_teslaTurret->GetModelPosition();
			//稼働範囲内なら
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

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_teslaTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_teslaTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_teslaTurret);
			MakeTeslaTurret();
			m_energy->SubEnergy(m_energy->COST_TESLATURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_teslaTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
	/// <summary>
	/// HolyTurret
	/// </summary>
	else if (m_turretType == enTurret_HolyTurret)
	{
		if (m_isGorstModelNewGO)
		{
			m_holyTurret = NewGO<HolyTurret>(0, "turret");
			m_holyTurret->SetModelPosition(m_cursorPosition);
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_holyTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z >= -8000.0f)
			{
				EffectPlayCursorAfter(m_holyTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_holyTurret->SetModelPosition(m_cursorPosition);
		}

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_holyTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z <= 0.0f)
			{
				EffectPlayCursorAfter(m_holyTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_holyTurret->SetModelPosition(m_cursorPosition);
		}

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_holyTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x >= -3200.0f)
			{
				EffectPlayCursorAfter(m_holyTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_holyTurret->SetModelPosition(m_cursorPosition);
		}

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_holyTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x <= 3200.0f)
			{
				EffectPlayCursorAfter(m_holyTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			else
			{
				m_energy->SoundPlayNotEnoughCost();
			}
			m_holyTurret->SetModelPosition(m_cursorPosition);
		}

		//Rボタン(Lキー)
		if (g_pad[0]->IsTrigger(enButtonRB2))
		{
			m_holyTurret->SetModelRotationTurnRight();
			m_rotation += 180.0f;
			SoundPlayCursorAfter();
		}

		//Lボタン(Iキー)
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			m_holyTurret->SetModelRotationTurnLeft();
			m_rotation -= 180.0f;
			SoundPlayCursorAfter();
		}

		//Aボタン(Jキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_holyTurret);
			MakeHolyTurret();
			m_energy->SubEnergy(m_energy->COST_HOLYTURRET);
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		//Bボタン(Kキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonB) && m_leftWindow->GetButtonReady() == true)
		{
			DeleteGO(m_holyTurret);
			m_leftWindow->SoundPlayWindow();
			m_leftWindow->SetOperationState(enOperationState_SelectTurret_LeftWindow);
			m_isModelNewGO = false;
		}
	}
}

void TurretManager::DeleteTurret()
{
	//削除確認画面の時
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
	
	//タレットが存在している箇所を選択している状態でSelect
	if (m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true && m_leftWindowDelete[m_leftWindow->GetSelectTurretNumber()]->GetIsDraw() == true)
	{
		m_turretDeleteState = enDeleteState_Cancel;
		m_leftWindow->SetOperationState(enOperationState_DeleteCheck_LeftWindow);
		m_leftWindow->SoundPlayWindow();
		m_deleteSpriteScale = 0.0f;
	}

	//Delete確認ウィンドウでCancelが選択されている時に右キー
	else if (m_turretDeleteState == enDeleteState_Cancel && g_pad[0]->IsTrigger(enButtonRight))
	{
		m_turretDeleteState = enDeleteState_Delete;
		m_leftWindow->SoundPlayChoice();
	}

	//Delete確認ウィンドウでCancelが選択されている時にSelect
	else if (m_turretDeleteState == enDeleteState_Cancel && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
	{
		m_turretDeleteState = enDeleteState_Null;
		m_leftWindow->SetOperationState(enOperationState_Delete_LeftWindow);
		m_leftWindow->SoundPlayWindow();
		m_deleteSpriteScale = 0.0f;
	}

	//Delete確認ウィンドウでDeleteが選択されている時に左キー
	else if (m_turretDeleteState == enDeleteState_Delete && g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_turretDeleteState = enDeleteState_Cancel;
		m_leftWindow->SoundPlayChoice();
	}

	//Delete確認ウィンドウでDeleteが選択されている時にSelect
	else if (m_turretDeleteState == enDeleteState_Delete && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
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
			//削除したタレット以降のタレットの画像を差し替える
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

void TurretManager::MakeGeneratorTurret()
{
	auto* turret = NewGO<GeneratorTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enTurret_GeneratorTurret);
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

void TurretManager::MakeHolyTurret()
{
	auto* turret = NewGO<HolyTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
	turret->SetModelRotation(m_rotation);
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_HolyTurret);
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

void TurretManager::EffectPlayCursorAfter(const Vector3& position)
{
	m_cursorAfterEF = NewGO<EffectEmitter>(0);
	m_cursorAfterEF->Init(enEffectNumber_CursorAfter);
	m_cursorAfterEF->SetPosition(position);
	m_cursorAfterEF->SetScale(Vector3::One * 100.0f);
	m_cursorAfterEF->Play();
}

void TurretManager::SoundPlayCursorAfter()
{
	m_cursorAfterSE = NewGO<SoundSource>(0);
	m_cursorAfterSE->Init(enSoundNumber_CursorAfter);
	m_cursorAfterSE->SetVolume(0.1f);
	m_cursorAfterSE->Play(false);
}

void TurretManager::SoundPlaySetTurret()
{
	m_setTurretSE = NewGO<SoundSource>(0);
	m_setTurretSE->Init(enSoundNumber_SetTurret);
	m_setTurretSE->SetVolume(0.15f);
	m_setTurretSE->Play(false);
}