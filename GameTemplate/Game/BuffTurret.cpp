#include "stdafx.h"
#include "BuffTurret.h"

#include "Energy.h"
#include "LeftWindow.h"
#include "TurretManager.h"

bool BuffTurret::Start()
{
	//FindGO
	m_energy = FindGO<Energy>("energy");
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	//�^���b�g
	m_turretBaseMR.Init("Assets/ModelData/Turret/BuffTurretBase.tkm", ShadowRecieveAndDrop, true);
	m_turretBaseMR.SetPosition(m_modelPosition);
	m_turretBaseMR.SetRotation(m_modelRotation);
	m_turretBaseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretBaseMR.Update();
	m_turretMR.Init("Assets/ModelData/Turret/BuffTurret.tkm", ShadowRecieveAndDrop, true);
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretMR.Update();

	//�y��
	m_baseMR.Init("Assets/ModelData/Turret/Base.tkm", ShadowRecieveAndDrop, true);
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.SetRotation(m_modelRotation);
	m_baseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_baseMR.Update();

	m_addGenerationTurret = true;

	return true;
}

void BuffTurret::Move()
{
	//����\�Ȃ�
	if (m_moveReady == true)
	{
		m_modelRotation.AddRotationDegY(2.0f);
		if (m_addGenerationTurret == true)
		{
			m_energy->AddGenerationTurret();
			m_addGenerationTurret = false;
		}
	}
}

void BuffTurret::Update()
{
	Move();

	//�X�V����
	m_turretBaseMR.SetPosition(m_modelPosition);
	m_turretBaseMR.Update();
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
}

void BuffTurret::Render(RenderContext& renderContext)
{
	m_turretBaseMR.Draw(renderContext);
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
}