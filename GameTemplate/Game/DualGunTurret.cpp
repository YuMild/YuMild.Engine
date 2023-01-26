#include "stdafx.h"
#include "DualGunTurret.h"

#include "Game.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP		= 200;
	const float FIRERATE	= 0.1f;
	const float ATTACKPOWER	= 50.0f;
	const float ATTACKRANGE	= 1000.0f;
}

bool DualGunTurret::Start()
{
	//�^���b�g
	m_turretMR.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowNone,true);
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

	//�˒��͈�
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Circle.tkm", Dithering,true);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.25f,1.0f,0.25f });
	m_attackRangeMR.Update();

	//�G�t�F�N�g��o�^
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/DualGunTurret.efk");

	//�����̐���
	g_soundEngine->ResistWaveFileBank(enSoundNumber_DualGunTurret, "Assets/sound/DualGunTurret.wav");

	//HP��ݒ�
	m_maxHp	= MAX_HP;
	m_hp = m_maxHp;

	return true;
}

void DualGunTurret::Move()
{
	//�̗͂������Ȃ�����
	if (m_hp <= 0)
	{
		DeleteGO(this);
	}

	//�f�o�t�Ɋ|�����Ă��Ȃ�������
	if (m_debuffTimer <= 0.0f)
	{
		m_fireRate += g_gameTime->GetFrameDeltaTime();
	}
	//�|�����Ă�����
	else
	{
		m_debuffTimer -= g_gameTime->GetFrameDeltaTime();
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 2;
	}

	//����\�Ȃ�
	if (m_moveReady == true)
	{
		//�˒���蒷�����OK
		m_difference = { 10000.0f,10000.0f,10000.0f };
		//���b�N�I���������ۂ�
		m_enemys = FindGOs<EnemyObject>("normal");
		for (auto enemys : m_enemys)
		{
			//�S�Ă̓G�Ƃ̋����𑪂�
			Vector3 enemysPosition = { enemys->GetPosition().x,0.0f,enemys->GetPosition().z };
			Vector3 modelPosition = { m_modelPosition.x,0.0f,m_modelPosition.z };
			Vector3 difference = enemysPosition - modelPosition;
			//�˒��O�Ȃ�߂�
			if (difference.Length() >= ATTACKRANGE)
			{
				continue;
			}
			//�˒����Ȃ瑱�s
			if (difference.Length() < m_difference.Length())
			{
				//���b�N�I��
				m_lockOnPosition = enemys->GetPosition();

				//���K��
				m_difference = difference;
				m_difference.Normalize();

				//���f���̉�]
				Vector3 rotation = m_difference;
				rotation.y = 0.0f;
				rotation.Normalize();
				m_modelRotation.SetRotationYFromDirectionXZ(rotation);
				m_turretMR.SetRotation(m_modelRotation);
				m_turretMR.Update();

				//���˃��[�g
				if (m_fireRate >= FIRERATE)
				{
					enemys->SubHP(ATTACKPOWER);
					EffectPlayHit(m_lockOnPosition);
					SoundPlayFire();
					m_fireRate = 0.0f;
				}
			}
		}
	}
}

void DualGunTurret::Update()
{
	Move();

	//�X�V����
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}
}

void DualGunTurret::EffectPlayHit(const Vector3& position)
{
	m_hitEF = NewGO<EffectEmitter>(0);
	m_hitEF->Init(2);
	m_hitEF->SetPosition({ position.x,position.y + 200.0f,position.z + 300.0f });
	m_hitEF->SetScale(Vector3::One * 150.0f);
	m_hitEF->Play();
}

void DualGunTurret::SoundPlayFire()
{
	m_fireSE = NewGO<SoundSource>(0);
	m_fireSE->Init(enSoundNumber_DualGunTurret);
	m_fireSE->SetVolume(0.025f);
	m_fireSE->Play(false);
}