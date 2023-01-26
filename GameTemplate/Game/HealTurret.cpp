#include "stdafx.h"
#include "HealTurret.h"

#include "Energy.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP = 200;
}

bool HealTurret::Start()
{
	//�^���b�g
	m_turretBaseMR.Init("Assets/ModelData/Turret/HealTurretBase.tkm", ShadowNone, true);
	m_turretBaseMR.SetPosition(m_modelPosition);
	m_turretBaseMR.SetRotation(m_modelRotation);
	m_turretBaseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretBaseMR.Update();
	m_turretMR.Init("Assets/ModelData/Turret/HealTurret.tkm", ShadowNone, true);
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

	//HP��ݒ�
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;

	return true;
}

void HealTurret::Move()
{
	//�̗͂������Ȃ�����
	if (m_hp <= 0)
	{
		DeleteGO(this);
	}

	//����\�Ȃ�
	if (m_moveReady == true)
	{
		m_turrets = FindGOs<TurretObject>("turret");
		for (auto turrets : m_turrets)
		{
			//�S�Ẵ^���b�g�Ƃ̋��������
			Vector3 difference = turrets->GetModelPosition() - m_modelPosition;
			//�˒����Ȃ�
			if (difference.Length() <= 1000.0f && turrets->GetAttackReady() == true)
			{
				turrets->SetModelRotationTurnRight();
			}
		}
		m_modelRotation.AddRotationDegY(2.0f);
	}
}

void HealTurret::Update()
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

void HealTurret::Render(RenderContext& renderContext)
{
	m_turretBaseMR.Draw(renderContext);
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
}