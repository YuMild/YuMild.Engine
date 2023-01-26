#include "stdafx.h"
#include "TeslaTurret.h"

#include "Game.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP		= 200;
	const float FIRERATE	= 2.0f;
	const float ATTACKPOWER	= 300.0f;
	const float ATTACKRANGE	= 2000.0f;
	const float BINDTIME	= 0.5f;
}

bool TeslaTurret::Start()
{
	//�^���b�g
	m_turretMR.Init("Assets/ModelData/Turret/TeslaTurret.tkm", ShadowNone, true);
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
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Circle.tkm", Dithering, true);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.5f,1.0f,0.5f });
	m_attackRangeMR.Update();

	//�G�t�F�N�g��o�^
	EffectEngine::GetInstance()->ResistEffect(7, u"Assets/effect/TeslaTurret.efk");

	//�����̐���
	g_soundEngine->ResistWaveFileBank(enSoundNumber_TeslaTurret, "Assets/sound/TeslaTurret.wav");

	//HP��ݒ�
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;

	return true;
}

void TeslaTurret::Move()
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

				//���˃��[�g
				if (m_fireRate >= FIRERATE)
				{
					enemys->SubHP(ATTACKPOWER);
					enemys->SetBind(BINDTIME);
					EffectPlayHit(m_lockOnPosition);
					SoundPlayFire();
					m_fireRate = 0.0f;
				}
			}
		}
	}
}

void TeslaTurret::Update()
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

void TeslaTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}
}