#include "stdafx.h"
#include "TurretManager.h"

#include "Energy.h"
#include "LeftWindow.h"
#include "LeftWindowDelete.h"

#include "DualGunTurret.h"
#include "LaserTurret.h"
#include "RocketTurret.h"
#include "GenerationTurret.h"

namespace
{
	//タレットの生産コスト
	float COST_DUALGUNTURRET = 100.0f;
	float COST_LASERTURRET = 200.0f;
	float COST_ROCKETTURRET = 400.0f;
	float COST_GENERATIONTURRET = 400.0f;

	//Delete
	float DELETE_SPRITE_SIZE_WIDTH = 1280.0f;
	float DELETE_SPRITE_SIZE_HEIGHT = 720.0f;

	//タレットの移動間隔
	float TURRET_POSITION_MOVE_NUM = 393.0f;

	//カーソル
	Vector3 CURSOR_POSITION = { 200.0f,0.0f,190.0f };
}

bool TurretManager::Start()
{
	//FindGO
	m_energy = FindGO<Energy>("energy");
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	//カーソルポジションをデフォルト値に設定
	m_cursorPosition = CURSOR_POSITION;

	//削除用の画像のポジションを設定
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

	//GridCursor
	m_gridCursor.Init("Assets/ModelData/Turret/RocketTurret.tkm", Dithering);
	m_gridCursor.SetScale({ 1.0f,1.0f,1.0f });

	//Deleteウィンドウ
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

	//削除用の画像を生成
	for (int i = 0; i < 12; i++)
	{
		m_leftWindowDelete[i] = NewGO<LeftWindowDelete>(0, "leftWindowDelete");
		m_leftWindowDelete[i]->Init(enInitDeleteTurretSprite_Null); 
		m_leftWindowDelete[i]->SetPosition(m_deleteSpritePosition[m_turretsSum]);
	}

	//エフェクトの作成
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/CursorAfter.efk");

	//音声の作成
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/CursorAfter2.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/SetTurret.wav");

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
	switch (m_turretType)
	{
	case enTurret_DualGunTurret:

		if (m_isGorstModelNewGO)
		{
			m_dualGunTurret= NewGO<DualGunTurret>(0, "turret");
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
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
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
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
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
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
				EffectPlayCursorAfter(m_dualGunTurret->GetModelPosition());
				SoundPlayCursorAfter();
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_dualGunTurret->SetModelPosition(m_cursorPosition);
			m_dualGunTurret->Update();
		}

		//Selectボタン(Spaceキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_dualGunTurret);
			MakeDualGunTurret();
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	case enTurret_LaserTurret:

		if (m_isGorstModelNewGO)
		{
			m_laserTurret = NewGO<LaserTurret>(0, "turret");
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

		//Selectボタン(Spaceキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_laserTurret);
			MakeLaserTurret();
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	case enTurret_RocketTurret:

		if (m_isGorstModelNewGO)
		{
			m_rocketTurret = NewGO<RocketTurret>(0, "turret");
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

		//Selectボタン(Spaceキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_rocketTurret);
			MakeRocketTurret();
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	case enTurret_GenerationTurret:

		if (m_isGorstModelNewGO)
		{
			m_generationTurret = NewGO<GenerationTurret>(0, "turret");
			m_generationTurret->SetModelPosition(m_cursorPosition);
			m_generationTurret->Update();
			m_isGorstModelNewGO = false;
		}

		//上ボタン(8キー)
		if (g_pad[0]->IsTrigger(enButtonUp))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z >= -9600.0f)
			{
				m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
			m_generationTurret->Update();
		}

		//下ボタン(2キー)
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.z <= 0.0f)
			{
				m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
			m_generationTurret->Update();
		}

		//右ボタン(6キー)
		if (g_pad[0]->IsTrigger(enButtonRight))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x >= -3200.0f)
			{
				m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
			m_generationTurret->Update();
		}

		//左ボタン(4キー)
		if (g_pad[0]->IsTrigger(enButtonLeft))
		{
			m_cursorPosition = m_generationTurret->GetModelPosition();
			//稼働範囲内なら
			if (m_cursorPosition.x <= 3200.0f)
			{
				m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
			}
			m_generationTurret->SetModelPosition(m_cursorPosition);
			m_generationTurret->Update();
		}

		//Selectボタン(Spaceキー)
		if (m_leftWindow->GetOperationState() == enOperationState_SetTurret_LeftWindow && g_pad[0]->IsTrigger(enButtonA) && m_leftWindow->GetButtonReady() == true)
		{
			m_leftWindow->SetButtonDelay();
			DeleteGO(m_generationTurret);
			MakeGenerationTurret();
			SoundPlaySetTurret();
			m_leftWindow->SetOperationState(enOperationState_Normal_LeftWindow);
		}

		break;

	default:

		break;
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

void TurretManager::MakeDualGunTurret()
{
	auto* turret = NewGO<DualGunTurret>(0, "turret");
	turret->SetModelPosition(m_cursorPosition);
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
	turret->SetAttackReady(true);
	m_turrets.push_back(turret);
	m_leftWindowDelete[m_turretsSum]->Init(enInitDeleteTurretSprite_GenerationTurret);
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