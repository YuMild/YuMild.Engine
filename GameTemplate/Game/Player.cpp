#include "stdafx.h"
#include "Player.h"

namespace
{
	Vector3 STAGE_FIRST_POSITION = { 0.0f,0.0f,0.0f };
	Vector3 STAGE_FIRST_SCALE = { 1.0f,1.0f,1.0f };

	float TURRET_POSITION_MOVE_NUM = 393.0f;
}

bool Player::Start()
{
	m_gridModelRender.Init("Assets/ModelData/Stage/Grid.tkm", ShadowRecieveAndDrop);
	m_gridModelRender.SetPosition(STAGE_FIRST_POSITION);
	m_gridModelRender.SetScale(STAGE_FIRST_SCALE);
	m_gridModelRender.Update();

	return true;
}

void Player::OperationNormal()
{
	//Start�{�^��(Enter�L�[)
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		//���샂�[�h��ύX
		m_operationState = enOparationStateSelectTurret;
	}

	//A�{�^��(J�L�[)
	if (g_pad[0]->IsPress(enButtonA))
	{
		//�J�����̍��x���グ��
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y + 100.0f,g_camera3D->GetPosition().z });
	}

	//B�{�^��(K�L�[)
	if (g_pad[0]->IsPress(enButtonB))
	{
		//�J�����̍��x��������
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y - 100.0f,g_camera3D->GetPosition().z });
	}
}

void Player::OperationSelectTurret()
{
	//��{�^��(8�L�[)
	if (g_pad[0]->IsTrigger(enButtonUp) && m_selectTurretNumber >= 4)
	{
		m_selectTurretNumber -= 4;
	}

	//���{�^��(2�L�[)
	if (g_pad[0]->IsTrigger(enButtonDown) && m_selectTurretNumber <= 7)
	{
		m_selectTurretNumber += 4;
	}

	//�E�{�^��(6�L�[)
	if (g_pad[0]->IsTrigger(enButtonRight) && m_selectTurretNumber != 3 && m_selectTurretNumber != 7 && m_selectTurretNumber != 11)
	{
		m_selectTurretNumber += 1;
	}

	//���{�^��(4�L�[)
	if (g_pad[0]->IsTrigger(enButtonLeft) && m_selectTurretNumber != 0 && m_selectTurretNumber != 4 && m_selectTurretNumber != 8)
	{
		m_selectTurretNumber -= 1;
	}

	//Start�{�^��(Enter�L�[)
	if (g_pad[0]->IsTrigger(enButtonSelect) && m_operationState == enOparationStateSelectTurret)
	{
		if (m_selectTurretNumber == enTurretDualGunTurret)
		{
			m_dualGunTurret = NewGO<DualGunTurret>(0, "dualGunTurret");
		}
		//���샂�[�h��ύX
		m_operationState = enOparationStateSetTurret;
	}
}

void Player::OperationSetTurret()
{
	//��{�^��(8�L�[)
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//�ғ��͈͓��Ȃ�
		if (m_cursorPosition.z >= -9600.0f)
		{
			m_cursorPosition.z -= TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//���{�^��(2�L�[)
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//�ғ��͈͓��Ȃ�
		if (m_cursorPosition.z <= 0.0f)
		{
			m_cursorPosition.z += TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//�E�{�^��(6�L�[)
	if (g_pad[0]->IsTrigger(enButtonRight))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//�ғ��͈͓��Ȃ�
		if (m_cursorPosition.x >= -3200.0f)
		{
			m_cursorPosition.x -= TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//���{�^��(4�L�[)
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_cursorPosition = m_dualGunTurret->GetPosition();
		//�ғ��͈͓��Ȃ�
		if (m_cursorPosition.x <= 3200.0f)
		{
			m_cursorPosition.x += TURRET_POSITION_MOVE_NUM;
		}
		m_dualGunTurret->SetPosition(m_cursorPosition);
	}

	//Start�{�^��(Enter�L�[)
	if (g_pad[0]->IsTrigger(enButtonSelect) && m_operationState == enOparationStateSetTurret)
	{
		//���샂�[�h��ύX
		m_operationState = enOparationStateNormal;
	}

	//X�{�^��(L�{�^��)
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		m_dualGunTurret->RotationTurnRight();
	}

	//Y�{�^��(I�{�^��)
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		m_dualGunTurret->RotationTurnLeft();
	}

	//A�{�^��(J�L�[)
	if (g_pad[0]->IsPress(enButtonA))
	{
		//�J�����̍��x���グ��
		g_camera3D->SetPosition({ g_camera3D->GetPosition().x,g_camera3D->GetPosition().y + 100.0f,g_camera3D->GetPosition().z });
	}

	//B�{�^��(K�L�[)
	if (g_pad[0]->IsPress(enButtonB))
	{
		//�J�����̍��x��������
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