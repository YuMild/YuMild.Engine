#include "stdafx.h"
#include "LeftWindow.h"

#include "Player.h"
#include "TurretManager.h"

namespace
{
	float DEFAULT_SPRITE_SIZE = 720.0f;
	float MOVE_X_DEFAULT = 50.0f;
	float MOVE_X_LIMIT = 400.0f;
	Vector3 DEFAULT_POSITION = { -950.0f,0.0f,0.0f };
}

bool LeftWindow::Start()
{
	//FindGO
	m_player = FindGO<Player>("player");
	m_turretManager = FindGO<TurretManager>("turretManager");

	//モデルの生成
	m_gridMR.Init("Assets/ModelData/Stage/Grid.tkm", ShadowRecieveAndDrop);
	m_gridMR.SetPosition(Vector3::Zero);
	m_gridMR.SetScale(Vector3::One);
	m_gridMR.Update();

	//画像の生成
	//枠
	m_frameSR.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_frameSR.SetPosition(DEFAULT_POSITION);
	m_frameSR.SetScale({ 1.0f,1.0f,1.0f });
	m_frameSR.Update();
	//タレット詳細
	m_dualGunTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_DualGunTurret_Detail.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_dualGunTurret_DetailSR.SetPosition(DEFAULT_POSITION);
	m_dualGunTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_dualGunTurret_DetailSR.Update();
	m_laserTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_LaserTurret_Detail.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_laserTurret_DetailSR.SetPosition(DEFAULT_POSITION);
	m_laserTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_laserTurret_DetailSR.Update();
	m_rocketTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_RocketTurret_Detail.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_rocketTurret_DetailSR.SetPosition(DEFAULT_POSITION);
	m_rocketTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_rocketTurret_DetailSR.Update();
	//ウィンドウ背景
	m_weapons_BackGroundSR.Init("Assets/sprite/LeftWindow/LeftWindow_WeaponsBackGround.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_weapons_BackGroundSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_weapons_BackGroundSR.SetScale({ 1.0f,1.0f,1.0f });
	m_weapons_BackGroundSR.Update();
	m_delete_BackGroundSR.Init("Assets/sprite/LeftWindow/LeftWindow_DeleteBackGround.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_delete_BackGroundSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_delete_BackGroundSR.SetScale({ 1.0f,1.0f,1.0f });
	m_delete_BackGroundSR.Update();
	m_turret_BackGroundSR.Init("Assets/sprite/LeftWindow/LeftWindow_TurretBackGround.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_turret_BackGroundSR.SetPosition(DEFAULT_POSITION);
	m_turret_BackGroundSR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_BackGroundSR.Update();

	//音声の生成
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Choice.wav");

	//タレット背景の位置
	m_turretBackGroundPosition[0] = { -950.0f,0.0f,0.0f };
	m_turretBackGroundPosition[1] = { -865.0f,0.0f,0.0f };
	m_turretBackGroundPosition[2] = { -780.0f,0.0f,0.0f };
	m_turretBackGroundPosition[3] = { -695.0f,0.0f,0.0f };
	m_turretBackGroundPosition[4] = { -950.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[5] = { -865.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[6] = { -780.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[7] = { -695.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[8] = { -950.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[9] = { -865.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[10] = { -780.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[11] = { -695.0f,-200.0f,0.0f };

	return true;
}

void LeftWindow::OperationNormal()
{
	//ウィンドウを左にスライド
	if (m_move_Number >= MOVE_X_DEFAULT)
	{
		m_move_Number -= 50.0f;
	}

	//LB1ボタン(Bキー)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_Normal_LeftWindow)
	{
		//操作モードを変更
		m_operationState = enOperationState_SelectTurret_LeftWindow;
		SoundPlayWindow();
	}
}

void LeftWindow::OperationSelectTurret()
{
	//ウィンドウを右にスライド
	if (m_move_Number <= MOVE_X_LIMIT)
	{
		m_move_Number += 50.0f;
	}

	//上ボタン(8キー)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		TurretCursorUp();
	}

	//下ボタン(2キー)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		TurretCursorDown();
	}

	//右ボタン(6キー)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		TurretCursorRight();
	}

	//左ボタン(4キー)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		TurretCursorLeft();
	}
	
	//Startボタン(Enterキー)
	if (g_pad[0]->IsTrigger(enButtonStart) && m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		//操作モードを変更
		m_operationState = enOperationState_SetTurret_LeftWindow;
		SoundPlayWindow();
		
		if (m_selectTurretNumber == enTurret_DualGunTurret)
		{
			m_turretManager->Init(enTurret_DualGunTurret);
		}
		else if (m_selectTurretNumber == enTurret_LaserTurret)
		{
			m_turretManager->Init(enTurret_LaserTurret);
		}
		else if (m_selectTurretNumber == enTurret_RocketTurret)
		{
			m_turretManager->Init(enTurret_RocketTurret);
		}

		m_selectTurretNumber = 0;
	}

	//LB1ボタン(Bキー)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		//操作モードを変更
		m_operationState = enOperationState_Delete_LeftWindow;
		SoundPlayWindow();
		m_selectTurretNumber = 0;
	}
}

void LeftWindow::OperationSetTurret()
{
	//ウィンドウを左にスライド
	if (m_move_Number >= MOVE_X_DEFAULT)
	{
		m_move_Number -= 50.0f;
	}
}

void LeftWindow::OperationDelete()
{
	//上ボタン(8キー)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		TurretCursorUp();
	}

	//下ボタン(2キー)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		TurretCursorDown();
	}

	//右ボタン(6キー)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		TurretCursorRight();
	}

	//左ボタン(4キー)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		TurretCursorLeft();
	}
	
	//LB1ボタン(Bキー)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_Delete_LeftWindow)
	{
		//操作モードを変更
		m_operationState = enOperationState_Normal_LeftWindow;
		m_selectTurretNumber = 0;
	}
}

void LeftWindow::Update()
{
	if (m_operationState == enOperationState_Normal_LeftWindow)
	{
		OperationNormal();
	}
	else if (m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		OperationSelectTurret();
	}
	else if (m_operationState == enOperationState_SetTurret_LeftWindow)
	{
		OperationSetTurret();
	}
	else if (m_operationState == enOperationState_Delete_LeftWindow)
	{
		OperationDelete();
	}

	//画像の更新
	m_frameSR.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_frameSR.Update();
	m_turret_BackGroundSR.SetPosition({ m_turretBackGroundPosition[m_selectTurretNumber].x + m_move_Number, m_turretBackGroundPosition[m_selectTurretNumber].y, m_turretBackGroundPosition[m_selectTurretNumber].z });
	m_turret_BackGroundSR.Update();
	m_dualGunTurret_DetailSR.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_dualGunTurret_DetailSR.Update();
	m_laserTurret_DetailSR.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_laserTurret_DetailSR.Update();
	m_rocketTurret_DetailSR.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_rocketTurret_DetailSR.Update();
}

void LeftWindow::Render(RenderContext& renderContext)
{
	//タレットセット時にグリッドモデルを表示
	if (m_operationState == enOperationState_SetTurret_LeftWindow)
	{
		m_gridMR.Draw(renderContext);
	}

	//右にスライドされている時だけ表示
	if (m_move_Number >= MOVE_X_LIMIT)
	{
		m_turret_BackGroundSR.Draw(renderContext);

		//タレット選択モード時
		if (m_operationState == enOperationState_SelectTurret_LeftWindow)
		{
			m_weapons_BackGroundSR.Draw(renderContext);
			m_dualGunTurret_DetailSR.Draw(renderContext);
			m_laserTurret_DetailSR.Draw(renderContext);
			m_rocketTurret_DetailSR.Draw(renderContext);
		}

		//タレット削除モード時
		if (m_operationState == enOperationState_Delete_LeftWindow)
		{
			m_delete_BackGroundSR.Draw(renderContext);
		}
	}

	m_frameSR.Draw(renderContext);
}