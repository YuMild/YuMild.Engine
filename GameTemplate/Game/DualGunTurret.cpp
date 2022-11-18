#include "stdafx.h"
#include "DualGunTurret.h"

#include "LeftWindow.h"

#include "TurretManager.h"

namespace
{
	float FIRERATE = 0.1f;
}

bool DualGunTurret::Start()
{
	//FindGO
	m_leftWindow = FindGO<LeftWindow>("leftWindow");
	m_turretManager = FindGO<TurretManager>("turretManager");

	//�^���b�g
	m_turretModel.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowRecieveAndDrop,true);
	m_turretModel.SetPosition(m_modelPosition);
	m_turretModel.SetRotation(m_modelRotation);
	m_turretModel.SetScale({ 1.0f,1.0f,1.0f });
	m_turretModel.Update();

	//�y��
	m_baseModel.Init("Assets/ModelData/Turret/Base.tkm", ShadowRecieveAndDrop, true);
	m_baseModel.SetPosition(m_modelPosition);
	m_baseModel.SetRotation(m_modelRotation);
	m_baseModel.SetScale({ 1.0f,1.0f,1.0f });
	m_baseModel.Update();

	//�����̐���
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/DualGunTurret.wav");

	return true;
}

void DualGunTurret::Attack()
{
	m_fireRate += g_gameTime->GetFrameDeltaTime();
	
	//�U���\�Ȃ�
	if (m_attackReady == true)
	{
		//�˒���蒷�����OK
		m_difference = { 10000.0f,10000.0f,10000.0f };
		//���b�N�I���������ۂ�
		m_enemys = FindGOs<EnemyObject>("ufo");
		for (auto lockOnObject : m_enemys)
		{
			//�S�Ă̓G�Ƃ̋����𑪂�
			Vector3 difference = lockOnObject->GetPosition() - m_modelPosition;
			//�˒����Ŋ���ԋ߂�������
			if (difference.Length() >= 1000.0f)
			{
				continue;
			}
			if (difference.Length() < m_difference.Length())
			{
				//m_lockOnPosition = lockOnObject->GetPosition();
				m_difference = difference;

				//���K��
				m_difference.Normalize();

				//���f���̉�]
				Vector3 rotation = m_difference;
				rotation.y = 0.0f;
				rotation.Normalize();
				Quaternion quaternion;
				quaternion.SetRotationYFromDirectionXZ(rotation);
				m_turretModel.SetRotation(quaternion);
				m_turretModel.Update();

				//���˃��[�g
				if (m_fireRate >= FIRERATE)
				{
					lockOnObject->SubHP(5.0f);
					SoundPlayFire();
					m_fireRate = 0.0f;
				}
			}
		}
	}
}

void DualGunTurret::Update()
{
	Attack();

	//�X�V����
	m_turretModel.SetPosition(m_modelPosition);
	m_turretModel.Update();
	m_baseModel.SetPosition(m_modelPosition);
	m_baseModel.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_turretModel.Draw(renderContext);
	m_baseModel.Draw(renderContext);
}