#include "stdafx.h"
#include "LeftWindow.h"

#include "Energy.h"
#include "Game.h"
#include "LeftWindowDelete.h"
#include "Player.h"
#include "TurretManager.h"

namespace
{
	//ウィンドウ
	const Vector3		LEFTWINDOW_POSITION							= { -950.0f,0.0f,0.0f };
	const float			LEFTWINDOW_SPRITE_SIZE						= 720.0f;
	const float			LEFTWINDOW_MOVE_X							= 50.0f;
	const float			LEFTWINDOW_MOVE_X_LIMIT						= 400.0f;

	//UIアニメーション
	const Vector3		CHOICEEFFECT_POSITION_SELECTTTURRET			= { -325.0f,300.0f,0.0f };
	const Vector3		CHOICEEFFECT_POSITION_SELECTTURRET_LIMIT	= { -325.0f,155.0f,0.0f };
	const Vector3		CHOICEEFFECT_POSITION_DELETETURRET			= { -325.0f,150.0f,0.0f };
	const Vector3		CHOICEEFFECT_POSITION_DELETETURRET_LIMIT	= { -325.0f,0.0f,0.0f };
	const float			CHOICEEFFECT_SIZE_X							= 55.0f;
	const float			CHOICEEFFECT_SIZE_Y							= 55.0f;

	//パラメーター
	const Vector3		PARAMETER_RANGE_POSITION					= { -971.0f,-109.5f,0.0f };
	const Vector3		PARAMETER_DAMAGE_POSITION					= { -971.0f,-150.5f,0.0f };
	const Vector3		PARAMETER_FIRERATE_POSITION					= { -971.0f,-191.5f,0.0f };
	const float			PARAMETER_MOVE_SPEED						= 0.02;

	//カメラポジション
	const Vector3		CAMERAPOSITION_NORMAL						= { 0.0f, 1500.0f, 1500.0f };
	const Vector3		CAMERAPOSITION_SPACESHIP					= { 0.0f, 1000.0f, 1500.0f };
}

bool LeftWindow::Start()
{
	//FindGO
	m_energy			= FindGO<Energy>("energy");
	m_gameCamera		= FindGO<GameCamera>("gameCamera");
	m_player			= FindGO<Player>("player");
	m_spaceShip			= FindGO<SpaceShip>("spaceShip");
	m_turretManager		= FindGO<TurretManager>("turretManager");

	//初期化
	m_choiceEffectPosition = CHOICEEFFECT_POSITION_SELECTTTURRET;

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
	m_detail_NormalTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_NormalTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_NormalTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_NormalTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_NormalTurretSR.Update();
	m_descride_NormalTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_NormalTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_NormalTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_NormalTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_NormalTurretSR.Update();
	m_detail_DualGunTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_DualGunTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_DualGunTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_DualGunTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_DualGunTurretSR.Update();
	m_descride_DualGunTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_DualGunTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_DualGunTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_DualGunTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_DualGunTurretSR.Update();
	m_detail_LaserTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_LaserTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_LaserTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_LaserTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_LaserTurretSR.Update();
	m_descride_LaserTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_LaserTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_LaserTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_LaserTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_LaserTurretSR.Update();
	m_detail_RocketTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_RocketTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_RocketTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_RocketTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_RocketTurretSR.Update();
	m_descride_RocketTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_RocketTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_RocketTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_RocketTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_RocketTurretSR.Update();
	m_detail_GenerationTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_GenerationTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_GenerationTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_GenerationTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_GenerationTurretSR.Update();
	m_descride_GenerationTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_GenerationTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_GenerationTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_GenerationTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_GenerationTurretSR.Update();
	m_detail_HealTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_HealTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_HealTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_HealTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_HealTurretSR.Update();
	m_descride_HealTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_HealTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_HealTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_HealTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_HealTurretSR.Update();
	m_detail_TeslaTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_TeslaTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_TeslaTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_TeslaTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_TeslaTurretSR.Update();
	m_descride_TeslaTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_TeslaTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_TeslaTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_TeslaTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_TeslaTurretSR.Update();
	m_detail_HolyTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_HolyTurret_Detail.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_detail_HolyTurretSR.SetPosition(LEFTWINDOW_POSITION);
	m_detail_HolyTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_detail_HolyTurretSR.Update();
	m_descride_HolyTurretSR.Init("Assets/sprite/LeftWindow/LeftWindow_HolyTurret_Descride.dds", LEFTWINDOW_SPRITE_SIZE, LEFTWINDOW_SPRITE_SIZE);
	m_descride_HolyTurretSR.SetPosition({ -500.0f,0.0f,0.0f });
	m_descride_HolyTurretSR.SetScale({ 1.0f,1.0f,1.0f });
	m_descride_HolyTurretSR.Update();
	//背景
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
	//UIアニメーション
	m_choiceEffectSR.Init("Assets/sprite/LeftWindow/ChoiceEffect.dds", CHOICEEFFECT_SIZE_X, CHOICEEFFECT_SIZE_Y);
	m_choiceEffectSR.SetPosition(m_choiceEffectPosition);
	m_choiceEffectSR.SetScale({ 1.0f,1.0f,1.0f });
	m_choiceEffectSR.Update();

	//タレット背景の位置
	m_turretBackGroundPosition[0]	= { -950.0f,0.0f,0.0f };
	m_turretBackGroundPosition[1]	= { -865.0f,0.0f,0.0f };
	m_turretBackGroundPosition[2]	= { -780.0f,0.0f,0.0f };
	m_turretBackGroundPosition[3]	= { -695.0f,0.0f,0.0f };
	m_turretBackGroundPosition[4]	= { -950.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[5]	= { -865.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[6]	= { -780.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[7]	= { -695.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[8]	= { -950.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[9]	= { -865.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[10]	= { -780.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[11]	= { -695.0f,-200.0f,0.0f };

	return true;
}

void LeftWindow::OperationNormal()
{
	//選択位置をデフォルトに設定
	m_selectTurretNumber = 0;

	//カメラ
	m_gameCamera->SetCameraState(enCameraState_Normal);

	/// <summary>
	/// ウィンドウを左にスライド
	/// </summary>
	if (m_moveNumber >= LEFTWINDOW_MOVE_X)
	{
		m_moveNumber -= 50.0f;
	}

	/// <summary>
	/// 操作モードを変更
	/// </summary>
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_Normal_LeftWindow)
	{
		m_operationState = enOperationState_SelectTurret_LeftWindow;
		SoundPlayWindow();
	}
}

void LeftWindow::OperationSelectTurret()
{
	/// <summary>
	/// ウィンドウを右にスライド
	/// </summary>
	if (m_moveNumber <= LEFTWINDOW_MOVE_X_LIMIT)
	{
		m_moveNumber += 50.0f;
	}

	//UIアニメーションの動作
	//徐々に下に
	m_choiceEffectPosition.y -= 1.0f;
	//下限まで下がったら上に戻す
	if (m_choiceEffectPosition.y <= CHOICEEFFECT_POSITION_SELECTTURRET_LIMIT.y)
	{
		m_choiceEffectPosition.y = CHOICEEFFECT_POSITION_SELECTTTURRET.y;
	}

	/// <summary>
	/// カーソルの移動
	/// </summary>
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		TurretCursorUp();
	}
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		TurretCursorDown();
	}
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		TurretCursorRight();
	}
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		TurretCursorLeft();
	}
	
	/// <summary>
	/// タレットの作成
	/// </summary>
	if (g_pad[0]->IsTrigger(enButtonB) && m_operationState == enOperationState_SelectTurret_LeftWindow && GetButtonReady() == true)
	{
		SetButtonDelay();

		/// <summary>
		/// NormalTurret
		/// </summary>
		if (m_selectTurretNumber == enTurret_NormalTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_NORMALTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_NormalTurret);
		}
		/// <summary>
		///	DualGunTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_DualGunTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_DUALGUNTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_DualGunTurret);
		}
		/// <summary>
		/// LaserTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_LaserTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_LASERTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_LaserTurret);
		}
		/// <summary>
		/// RocketTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_RocketTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_ROCKETTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_RocketTurret);
		}
		/// <summary>
		/// GeneratorTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_GeneratorTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_GENERATIONTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_GeneratorTurret);
		}
		/// <summary>
		/// HealTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_HealTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_HEALTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_HealTurret);
		}
		/// <summary>
		/// TeslaTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_TeslaTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_TESLATURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_TeslaTurret);
		}
		/// <summary>
		/// HolyTurret
		/// </summary>
		else if (m_selectTurretNumber == enTurret_HolyTurret)
		{
			if (m_energy->GetEnergy() <= m_energy->COST_HOLYTURRET)
			{
				m_energy->SoundPlayNotEnoughCost();
				return;
			}
			m_turretManager->Init(enTurret_HolyTurret);
		}

		m_operationState = enOperationState_SetTurret_LeftWindow;
		m_selectTurretNumber = 0;
		SoundPlayWindow();
	}

	/// <summary>
	/// 操作モードを変更
	/// </summary>
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		m_operationState = enOperationState_Delete_LeftWindow;
		m_selectTurretNumber = 0;
		SoundPlayWindow();
	}
}

void LeftWindow::OperationSetTurret()
{
	/// <summary>
	/// カメラを変更
	/// </summary>
	m_gameCamera->SetCameraState(enCameraState_SetTurret);
	
	//ウィンドウを左にスライド
	if (m_moveNumber >= LEFTWINDOW_MOVE_X)
	{
		m_moveNumber -= 50.0f;
	}
}

void LeftWindow::OperationDelete()
{
	//UIアニメーションの動作
	//徐々に下に
	m_choiceEffectPosition.y -= 1.0f;
	//下限まで下がったら上に戻す
	if (m_choiceEffectPosition.y <= CHOICEEFFECT_POSITION_DELETETURRET_LIMIT.y || m_choiceEffectPosition.y >= CHOICEEFFECT_POSITION_DELETETURRET.y)
	{
		m_choiceEffectPosition.y = CHOICEEFFECT_POSITION_DELETETURRET.y;
	}

	/// <summary>
	/// カーソルの移動
	/// </summary>
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		TurretCursorUp();
	}
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		TurretCursorDown();
	}
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		TurretCursorRight();
	}
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
	if (m_turrets.size() != 0 && m_turrets.size() > m_selectTurretNumber)
	{
		g_camera3D->SetTarget(m_turrets[m_selectTurretNumber]->GetModelPosition());
		g_camera3D->SetPosition({ m_turrets[m_selectTurretNumber]->GetModelPosition().x,m_turrets[m_selectTurretNumber]->GetModelPosition().y + 1000.0f,m_turrets[m_selectTurretNumber]->GetModelPosition().z + 2000.0f });
		m_gridCursorMR.SetPosition(m_turrets[m_selectTurretNumber]->GetModelPosition());
		m_gridCursorMR.Update();
	}
}

void LeftWindow::SetParameterBar()
{
	//初期化
	switch (m_selectTurretNumber)
	{
	case enTurret_NormalTurret:
		m_rangeNumber = 0.25f;
		m_damageNumber = 0.2f;
		m_fireRateNumber = 0.25f;
		break;
	case enTurret_DualGunTurret:
		m_rangeNumber = 0.25f;
		m_damageNumber = 0.1f;
		m_fireRateNumber = 1.0f;
		break;
	case enTurret_LaserTurret:
		m_rangeNumber = 1.0f;
		m_damageNumber = 0.5f;
		m_fireRateNumber = 0.25f;
		break;
	case enTurret_RocketTurret:
		m_rangeNumber = 0.75f;
		m_damageNumber = 0.75f;
		m_fireRateNumber = 0.1f;
		break;
	case enTurret_GeneratorTurret:
		m_rangeNumber = 0.0f;
		m_damageNumber = 0.0f;
		m_fireRateNumber = 0.0f;
		break;
	case enTurret_HealTurret:
		m_rangeNumber = 0.25f;
		m_damageNumber = 0.0f;
		m_fireRateNumber = 0.0f;
		break;
	case enTurret_TeslaTurret:
		m_rangeNumber = 0.75f;
		m_damageNumber = 0.75f;
		m_fireRateNumber = 0.1f;
		break;
	case enTurret_HolyTurret:
		m_rangeNumber = 1.0f;
		m_damageNumber = 0.0f;
		m_fireRateNumber = 0.05f;
		break;
	default:
		break;
	}

	//パラメーターバーの動作
	//Range
	if (m_rangeSetNumber < m_rangeNumber)
	{
		m_rangeSetNumber += PARAMETER_MOVE_SPEED;
	}
	if (m_rangeSetNumber > m_rangeNumber)
	{
		m_rangeSetNumber -= PARAMETER_MOVE_SPEED;
	}
	//Damage
	if (m_damageSetNumber < m_damageNumber)
	{
		m_damageSetNumber += PARAMETER_MOVE_SPEED;
	}
	if (m_damageSetNumber > m_damageNumber)
	{
		m_damageSetNumber -= PARAMETER_MOVE_SPEED;
	}
	//FireRate
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
	//パラメーターバー
	SetParameterBar();

	//ステート管理
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
	m_detail_NormalTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_NormalTurretSR.Update();
	m_detail_DualGunTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_DualGunTurretSR.Update();
	m_detail_LaserTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_LaserTurretSR.Update();
	m_detail_RocketTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_RocketTurretSR.Update();
	m_detail_GenerationTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_GenerationTurretSR.Update();
	m_detail_HealTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_HealTurretSR.Update();
	m_detail_TeslaTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_TeslaTurretSR.Update();
	m_detail_HolyTurretSR.SetPosition({ LEFTWINDOW_POSITION.x + m_moveNumber, LEFTWINDOW_POSITION.y, LEFTWINDOW_POSITION.z });
	m_detail_HolyTurretSR.Update();
	//UIアニメーション
	m_choiceEffectSR.SetPosition(m_choiceEffectPosition);
	m_choiceEffectSR.Update();
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
			//パラメーター
			m_parameter_RangeSR.Draw(renderContext);
			m_parameter_DamageSR.Draw(renderContext);
			m_parameter_FireRateSR.Draw(renderContext);
			//タレット
			m_weapons_BackGroundSR.Draw(renderContext);
			m_detail_NormalTurretSR.Draw(renderContext);
			m_detail_DualGunTurretSR.Draw(renderContext);
			m_detail_LaserTurretSR.Draw(renderContext);
			m_detail_RocketTurretSR.Draw(renderContext);
			m_detail_GenerationTurretSR.Draw(renderContext);
			m_detail_HealTurretSR.Draw(renderContext);
			m_detail_TeslaTurretSR.Draw(renderContext);
			m_detail_HolyTurretSR.Draw(renderContext);
			//説明文
			if (m_selectTurretNumber == enTurret_NormalTurret)
			{
				m_descride_NormalTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_DualGunTurret)
			{
				m_descride_DualGunTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_LaserTurret)
			{
				m_descride_LaserTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_RocketTurret)
			{
				m_descride_RocketTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_GeneratorTurret)
			{
				m_descride_GenerationTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_HealTurret)
			{
				m_descride_HealTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_TeslaTurret)
			{
				m_descride_TeslaTurretSR.Draw(renderContext);
			}
			else if (m_selectTurretNumber == enTurret_HolyTurret)
			{
				m_descride_HolyTurretSR.Draw(renderContext);
			}
		}

		//タレット削除モード時
		if (m_operationState == enOperationState_Delete_LeftWindow || m_operationState == enOperationState_DeleteCheck_LeftWindow)
		{
			m_gridCursorMR.Draw(renderContext);
			m_delete_BackGroundSR.Draw(renderContext);
		}

		m_choiceEffectSR.Draw(renderContext);
	}

	//フレーム
	m_frameSR.Draw(renderContext);
}

void LeftWindow::OperationDeleteCheck()
{

}

void LeftWindow::SoundPlayWindow()
{
	m_windowSE = NewGO<SoundSource>(0);
	m_windowSE->Init(enSoundNumber_Window);
	m_windowSE->SetVolume(1.0f);
	m_windowSE->Play(false);
}

void LeftWindow::SoundPlayChoice()
{
	m_choiceSE = NewGO<SoundSource>(0);
	m_choiceSE->Init(enSoundNumber_Choice);
	m_choiceSE->SetVolume(0.1f);
	m_choiceSE->Play(false);
}