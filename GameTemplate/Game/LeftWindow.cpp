#include "stdafx.h"
#include "LeftWindow.h"

#include "Player.h"
#include "TurretManager.h"

namespace
{
	float DEFAULT_SPRITE_SIZE = 720.0f;
	float DEFAULT_MOVE_WINDOW_X = 50.0f;
	float LIMIT_MOVE_WINDOW_X = 400.0f;
	float PARAMETER_MOVE_SPEED = 0.02;
	Vector3 DEFAULT_POSITION = { -950.0f,0.0f,0.0f };
	Vector3 DEFAULT_PARAMETER_RANGE_POSITION = { -971.0f,-128.5f,0.0f };
	Vector3 DEFAULT_PARAMETER_DAMAGE_POSITION = { -971.0f,-190.5f,0.0f };
	Vector3 DEFAULT_PARAMETER_FIRERATE_POSITION = { -971.0f,-252.5f,0.0f };
}

bool LeftWindow::Start()
{
	//FindGO
	m_player = FindGO<Player>("player");
	m_turretManager = FindGO<TurretManager>("turretManager");

	//���f���̐���
	m_gridMR.Init("Assets/ModelData/Stage/Grid.tkm", Dithering);
	m_gridMR.SetPosition({0.0f,-50,0.0f});
	m_gridMR.SetScale(Vector3::One);
	m_gridMR.Update();

	//�摜�̐���
	//�g
	m_frameSR.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_frameSR.SetPosition(DEFAULT_POSITION);
	m_frameSR.SetScale({ 1.0f,1.0f,1.0f });
	m_frameSR.Update();
	//�p�����[�^�[�o�[
	m_parameter_RangeSR.Init("Assets/sprite/LeftWindow/LeftWindow_ParameterBar.dds", 280.0f, 280.0f);
	m_parameter_RangeSR.SetPosition(DEFAULT_PARAMETER_RANGE_POSITION);
	m_parameter_RangeSR.SetScale({ 1.0f,1.0f,1.0f });
	m_parameter_RangeSR.Update();
	m_parameter_DamageSR.Init("Assets/sprite/LeftWindow/LeftWindow_ParameterBar.dds", 280.0f, 280.0f);
	m_parameter_DamageSR.SetPosition(DEFAULT_PARAMETER_DAMAGE_POSITION);
	m_parameter_DamageSR.SetScale({ 1.0f,1.0f,1.0f });
	m_parameter_DamageSR.Update();
	m_parameter_FireRateSR.Init("Assets/sprite/LeftWindow/LeftWindow_ParameterBar.dds", 280.0f, 280.0f);
	m_parameter_FireRateSR.SetPosition(DEFAULT_PARAMETER_FIRERATE_POSITION);
	m_parameter_FireRateSR.SetScale({ 1.0f,1.0f,1.0f });
	m_parameter_FireRateSR.Update();
	//�^���b�g�ڍ�
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
	//�E�B���h�E�w�i
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

	//�����̐���
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Window.wav");
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/Choice.wav");

	//�^���b�g�w�i�̈ʒu
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
	//�E�B���h�E�����ɃX���C�h
	if (m_move_Number >= DEFAULT_MOVE_WINDOW_X)
	{
		m_move_Number -= 50.0f;
	}

	//LB1�{�^��(B�L�[)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_Normal_LeftWindow)
	{
		//���샂�[�h��ύX
		m_operationState = enOperationState_SelectTurret_LeftWindow;
		SoundPlayWindow();
	}
}

void LeftWindow::OperationSelectTurret()
{
	//�E�B���h�E���E�ɃX���C�h
	if (m_move_Number <= LIMIT_MOVE_WINDOW_X)
	{
		m_move_Number += 50.0f;
	}

	//��{�^��(8�L�[)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		TurretCursorUp();
	}

	//���{�^��(2�L�[)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		TurretCursorDown();
	}

	//�E�{�^��(6�L�[)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		TurretCursorRight();
	}

	//���{�^��(4�L�[)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		TurretCursorLeft();
	}
	
	//Start�{�^��(Enter�L�[)
	if (g_pad[0]->IsTrigger(enButtonStart) && m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		//���샂�[�h��ύX
		m_operationState = enOperationState_SetTurret_LeftWindow;
		SoundPlayWindow();
		
		//�^���b�g���쐬
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

	//LB1�{�^��(B�L�[)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_SelectTurret_LeftWindow)
	{
		//���샂�[�h��ύX
		m_operationState = enOperationState_Delete_LeftWindow;
		SoundPlayWindow();
		m_selectTurretNumber = 0;
	}
}

void LeftWindow::OperationSetTurret()
{
	//�E�B���h�E�����ɃX���C�h
	if (m_move_Number >= DEFAULT_MOVE_WINDOW_X)
	{
		m_move_Number -= 50.0f;
	}
}

void LeftWindow::OperationDelete()
{
	//��{�^��(8�L�[)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		TurretCursorUp();
	}

	//���{�^��(2�L�[)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		TurretCursorDown();
	}

	//�E�{�^��(6�L�[)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		TurretCursorRight();
	}

	//���{�^��(4�L�[)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		TurretCursorLeft();
	}
	
	//LB1�{�^��(B�L�[)
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_operationState == enOperationState_Delete_LeftWindow)
	{
		//���샂�[�h��ύX
		m_operationState = enOperationState_Normal_LeftWindow;
		m_selectTurretNumber = 0;
	}
}

void LeftWindow::SetParameterBar()
{
	//������
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
	default:
		break;
	}

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

	//�摜�̍X�V
	m_frameSR.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_frameSR.Update();
	//�p�����[�^�[
	m_parameter_RangeSR.SetPosition({ DEFAULT_PARAMETER_RANGE_POSITION.x + m_move_Number, DEFAULT_PARAMETER_RANGE_POSITION.y, DEFAULT_PARAMETER_RANGE_POSITION.z });
	m_parameter_RangeSR.SetIsDisplayRestrictionRightSide(true);
	m_parameter_RangeSR.SetLimitedX(m_rangeSetNumber);
	m_parameter_RangeSR.Update();
	m_parameter_DamageSR.SetPosition({ DEFAULT_PARAMETER_DAMAGE_POSITION.x + m_move_Number, DEFAULT_PARAMETER_DAMAGE_POSITION.y, DEFAULT_PARAMETER_DAMAGE_POSITION.z });
	m_parameter_DamageSR.SetIsDisplayRestrictionRightSide(true);
	m_parameter_DamageSR.SetLimitedX(m_damageSetNumber);
	m_parameter_DamageSR.Update();
	m_parameter_FireRateSR.SetPosition({ DEFAULT_PARAMETER_FIRERATE_POSITION.x + m_move_Number, DEFAULT_PARAMETER_FIRERATE_POSITION.y, DEFAULT_PARAMETER_FIRERATE_POSITION.z });
	m_parameter_FireRateSR.SetIsDisplayRestrictionRightSide(true);
	m_parameter_FireRateSR.SetLimitedX(m_fireRateSetNumber);
	m_parameter_FireRateSR.Update();
	//�^���b�g
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
	//�^���b�g�Z�b�g���ɃO���b�h���f����\��
	if (m_operationState == enOperationState_SetTurret_LeftWindow)
	{
		m_gridMR.Draw(renderContext);
	}

	//�E�ɃX���C�h����Ă��鎞�����\��
	if (m_move_Number >= LIMIT_MOVE_WINDOW_X)
	{
		m_turret_BackGroundSR.Draw(renderContext);

		//�^���b�g�I�����[�h��
		if (m_operationState == enOperationState_SelectTurret_LeftWindow)
		{
			m_parameter_RangeSR.Draw(renderContext);
			m_parameter_DamageSR.Draw(renderContext);
			m_parameter_FireRateSR.Draw(renderContext);
			m_weapons_BackGroundSR.Draw(renderContext);
			m_dualGunTurret_DetailSR.Draw(renderContext);
			m_laserTurret_DetailSR.Draw(renderContext);
			m_rocketTurret_DetailSR.Draw(renderContext);
		}

		//�^���b�g�폜���[�h��
		if (m_operationState == enOperationState_Delete_LeftWindow)
		{
			m_delete_BackGroundSR.Draw(renderContext);
		}
	}

	m_frameSR.Draw(renderContext);
}