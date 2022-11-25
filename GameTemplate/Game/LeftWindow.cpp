#include "stdafx.h"
#include "LeftWindow.h"

#include "Player.h"
#include "TurretManager.h"

namespace
{
	//LeftWindow
	Vector3 LEFTWINDOW_POSITION = { -950.0f,0.0f,0.0f };
	float LEFTWINDOW_SPRITE_SIZE = 720.0f;
	float LEFTWINDOW_MOVE_X = 50.0f;
	float LEFTWINDOW_MOVE_X_LIMIT = 400.0f;

	//パラメーター
	Vector3 PARAMETER_RANGE_POSITION = { -971.0f,-128.5f,0.0f };
	Vector3 PARAMETER_DAMAGE_POSITION = { -971.0f,-190.5f,0.0f };
	Vector3 PARAMETER_FIRERATE_POSITION = { -971.0f,-252.5f,0.0f };
	float PARAMETER_MOVE_SPEED = 0.02;
}

bool LeftWindow::Start()
{
	//FindGO
	m_player = FindGO<Player>("player");
	m_turretManager = FindGO<TurretManager>("turretManager");

	//モデルの生成
	//グリッド
	m_gridMR.Init("Assets/ModelData/Stage/Grid.tkm", Dithering);
	m_gridMR.SetPosition({0.0f,-50,0.0f});
	m_gridMR.SetScale(Vector3::One);
	m_gridMR.Update();
	//カーソル
	m_gridCursorMR.Init("Assets/ModelData/Stage/GridCursor.tkm", Dithering);
	m_gridCursorMR.SetPosition({ 0.0f,-50,0.0f });
	m_gridCursorMR.SetScale(Vector3::One);
	m_gridCursorMR.Update();

	//画像の生成
	//枠
	m_frameSR.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_frameSR.SetPosition(LEFTWINDOW_POSITION);
	m_frameSR.SetScale({ 1.0f,1.0f,1.0f });
	m_frameSR.Update();
	//パラメーターバー
	m_parameter_RangeSR.Init("Assets/sprite/LeftWindow/LeftWindow_ParameterBar.dds", 280.0f, 280.0f);
	m_parameter_RangeSR.SetPosition(PARAMETER_RANGE_POSITION);
	m_parameter_RangeSR.SetScale({ 1.0f,1.0f,1.0f });
	m_parameter_RangeSR.Update();
	m_parameter_DamageSR.Init("Assets/sprite/LeftWindow/LeftWindow_ParameterBar.dds", 280.0f, 280.0f);
	m_parameter_DamageSR.SetPosition(PARAMETER_DAMAGE_POSITION);
	m_parameter_DamageSR.SetScale({ 1.0f,1.0f,1.0f });
	m_parameter_DamageSR.Update();
	m_parameter_FireRateSR.Init("Assets/sprite/LeftWindow/LeftWindow_ParameterBar.dds", 280.0f, 280.0f);
	m_parameter_FireRateSR.SetPosition(PARAMETER_FIRERATE_POSITION);
	m_parameter_FireRateSR.SetScale({ 1.0f,1.0f,1.0f });
	m_parameter_FireRateSR.Update();
	//タレット詳細
	m_dualGunTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_DualGunTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_dualGunTurret_DetailSR.SetPosition(LEFTWINDOW_POSITION);
	m_dualGunTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_dualGunTurret_DetailSR.Update();
	m_laserTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_LaserTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_laserTurret_DetailSR.SetPosition(LEFTWINDOW_POSITION);
	m_laserTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_laserTurret_DetailSR.Update();
	m_rocketTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_RocketTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_rocketTurret_DetailSR.SetPosition(LEFTWINDOW_POSITION);
	m_rocketTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_rocketTurret_DetailSR.Update();
	m_generationTurret_DetailSR.Init("Assets/sprite/LeftWindow/LeftWindow_GenerationTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_generationTurret_DetailSR.SetPosition(LEFTWINDOW_POSITION);
	m_generationTurret_DetailSR.SetScale({ 1.0f,1.0f,1.0f });
	m_generationTurret_DetailSR.Update();
	//ウィンドウ背景
	m_weapons_BackGroundSR.Init("Assets/sprite/LeftWindow/LeftWindow_WeaponsBackGround.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_weapons_BackGroundSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_weapons_BackGroundSR.SetScale({ 1.0f,1.0f,1.0f });
	m_weapons_BackGroundSR.Update();
	m_delete_BackGroundSR.Init("Assets/sprite/LeftWindow/LeftWindow_DeleteBackGround.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_delete_BackGroundSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_delete_BackGroundSR.SetScale({ 1.0f,1.0f,1.0f });
	m_delete_BackGroundSR.Update();
	m_turret_BackGroundSR.Init("Assets/sprite/LeftWindow/LeftWindow_TurretBackGround.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_turret_BackGroundSR.SetPosition(LEFTWINDOW_POSITION);
	m_turret_BackGroundSR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_BackGroundSR.Update();

	//音声の生成
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Window.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/Choice.wav");

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
	if (m_moveNumber >= LEFTWINDOW_MOVE_X)
	{
		m_moveNumber -= 50.0f;
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
	if (m_moveNumber <= LEFTWINDOW_MOVE_X_LIMIT)
	{
		m_moveNumber += 50.0f;
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
	
	//Selectボタン(Spaceキー)
	if (g_pad[0]->IsTrigger(enButtonSelect) && m_operationState == enOperationState_SelectTurret_LeftWindow && GetButtonReady() == true)
	{
		SetButtonDelay();
		//操作モードを変更
		m_operationState = enOperationState_SetTurret_LeftWindow;
		SoundPlayWindow();

		//タレットを作成
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
		else if (m_selectTurretNumber == enTurret_GenerationTurret)
		{
			m_turretManager->Init(enTurret_GenerationTurret);
		}

		//選択個所をリセット
		m_selectTurretNumber = 0;
	}

	//LB1ボタン(Bキー)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		//操作モードを変更
		m_operationState = enOperationState_Delete_LeftWindow;
		//選択個所をリセット
		m_selectTurretNumber = 0;
		SoundPlayWindow();
	}
}

void LeftWindow::OperationSetTurret()
{
	//ウィンドウを左にスライド
	if (m_moveNumber >= LEFTWINDOW_MOVE_X)
	{
		m_moveNumber -= 50.0f;
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

	//削除するタレットを表示
	m_turrets = FindGOs<TurretObject>("turret");

	if (m_turrets[m_selectTurretNumber] != nullptr)
	{
		m_gridCursorPosition = m_turrets[m_selectTurretNumber]->GetModelPosition();
		m_gridCursorMR.SetPosition(m_gridCursorPosition);
		m_gridCursorMR.Update();
	}
}

void LeftWindow::OperationDeleteCheck()
{
	
}

void LeftWindow::SetParameterBar()
{
	//初期化
	switch (m_selectTurretNumber)
	{
	case enTurret_DualGunTurret:
		m_rangeNumber = 0.25f;
		m_damageNumber = 0.1f;
		m_fireRateNumber = 0.75f;
		break;
	case enTurret_LaserTurret:
		m_rangeNumber = 0.5f;
		m_damageNumber = 0.5f;
		m_fireRateNumber = 0.25f;
		break;
	case enTurret_RocketTurret:
		m_rangeNumber = 0.75f;
		m_damageNumber = 0.75f;
		m_fireRateNumber = 0.1f;
		break;
	case enTurret_GenerationTurret:
		m_rangeNumber = 0.0f;
		m_damageNumber = 0.0f;
		m_fireRateNumber = 0.0f;
		break;
	default:
		break;
	}

	//パラメーターバーの動作
	if (m_rangeSetNumber < m_rangeNumber)
	{
		m_rangeSetNumber += PARAMETER_MOVE_SPEED;
	}
	if (m_rangeSetNumber > m_rangeNumber)
	{
		m_rangeSetNumber -= PARAMETER_MOVE_SPEED;
	}
	if (m_damageSetNumber < m_damageNumber)
	{
		m_damageSetNumber += PARAMETER_MOVE_SPEED;
	}
	if (m_damageSetNumber > m_damageNumber)
	{
		m_damageSetNumber -= PARAMETER_MOVE_SPEED;
	}
	if (m_fireRateSetNumber < m_fireRateNumber)
	{
		m_fireRateSetNumber += PARAMETER_MOVE_SPEED;
	}
	if (m_fireRateSetNumber > m_fireRateNumber)
	{
		m_fireRateSetNumber -= PARAMETER_MOVE_SPEED;
	}
}

void LeftWindow::Update()
{
	SetParameterBar();

	switch (m_operationState)
	{
	case enOperationState_Normal_LeftWindow:
		OperationNormal();
		break;
	case enOperationState_SelectTurret_LeftWindow:
		OperationSelectTurret();
		break;
	case enOperationState_SetTurret_LeftWindow:
		OperationSetTurret();
		break;
	case enOperationState_Delete_LeftWindow:
		OperationDelete();
		break;
	case enOperationState_DeleteCheck_LeftWindow:
		OperationDeleteCheck();
		break;
	default:
		break;
	}

	//ボタンが重複反応しないように
	m_buttonDelay += g_gameTime->GetFrameDeltaTime();
	if (m_buttonDelay >= 0.05)
	{
		m_buttonReady = true;
	}
	else
	{
		m_buttonReady = false;
	}

	//画像の更新
	m_frameSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_frameSR.Update();
	//パラメーター
	m_parameter_RangeSR.SetPosition({ PARAMETER_RANGE_POSITION.x + m_moveNumber, PARAMETER_RANGE_POSITION.y, PARAMETER_RANGE_POSITION.z });
	m_parameter_RangeSR.SetIsDisplayRestrictionRightSide(true);
	m_parameter_RangeSR.SetLimitedX(m_rangeSetNumber);
	m_parameter_RangeSR.Update();
	m_parameter_DamageSR.SetPosition({ PARAMETER_DAMAGE_POSITION.x + m_moveNumber, PARAMETER_DAMAGE_POSITION.y, PARAMETER_DAMAGE_POSITION.z });
	m_parameter_DamageSR.SetIsDisplayRestrictionRightSide(true);
	m_parameter_DamageSR.SetLimitedX(m_damageSetNumber);
	m_parameter_DamageSR.Update();
	m_parameter_FireRateSR.SetPosition({ PARAMETER_FIRERATE_POSITION.x + m_moveNumber, PARAMETER_FIRERATE_POSITION.y, PARAMETER_FIRERATE_POSITION.z });
	m_parameter_FireRateSR.SetIsDisplayRestrictionRightSide(true);
	m_parameter_FireRateSR.SetLimitedX(m_fireRateSetNumber);
	m_parameter_FireRateSR.Update();
	//タレット
	m_turret_BackGroundSR.SetPosition({ m_turretBackGroundPosition[m_selectTurretNumber].x + m_moveNumber, m_turretBackGroundPosition[m_selectTurretNumber].y, m_turretBackGroundPosition[m_selectTurretNumber].z });
	m_turret_BackGroundSR.Update();
	m_dualGunTurret_DetailSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_dualGunTurret_DetailSR.Update();
	m_laserTurret_DetailSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_laserTurret_DetailSR.Update();
	m_rocketTurret_DetailSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_rocketTurret_DetailSR.Update();
	m_generationTurret_DetailSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_generationTurret_DetailSR.Update();
}

void LeftWindow::Render(RenderContext& renderContext)
{
	//タレットセット時にグリッドモデルを表示
	if (m_operationState == enOperationState_SetTurret_LeftWindow)
	{
		m_gridMR.Draw(renderContext);
	}

	//右にスライドされている時だけ表示
	if (m_moveNumber >= LEFTWINDOW_MOVE_X_LIMIT)
	{
		m_turret_BackGroundSR.Draw(renderContext);

		//タレット選択モード時
		if (m_operationState == enOperationState_SelectTurret_LeftWindow)
		{
			m_parameter_RangeSR.Draw(renderContext);
			m_parameter_DamageSR.Draw(renderContext);
			m_parameter_FireRateSR.Draw(renderContext);
			m_weapons_BackGroundSR.Draw(renderContext);
			m_dualGunTurret_DetailSR.Draw(renderContext);
			m_laserTurret_DetailSR.Draw(renderContext);
			m_rocketTurret_DetailSR.Draw(renderContext);
			m_generationTurret_DetailSR.Draw(renderContext);
		}

		//タレット削除モード時
		if (m_operationState == enOperationState_Delete_LeftWindow || m_operationState == enOperationState_DeleteCheck_LeftWindow)
		{
			m_gridCursorMR.Draw(renderContext);
			m_delete_BackGroundSR.Draw(renderContext);
		}
	}

	//フレーム
	m_frameSR.Draw(renderContext);
}