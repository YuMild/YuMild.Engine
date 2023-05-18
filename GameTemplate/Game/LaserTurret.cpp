#include "stdafx.h"
#include "LaserTurret.h"

#include "Game.h"

namespace
{
	const float	MAX_HP				= 200.0f;
	const float FIRERATE			= 2.0f;
	const float ATTACKPOWER			= 30.0f;
	const float EFFECTSIZE_SMOKE	= 50.0f;
	const float EFFECTSIZE_LASER	= 200.0f;
	const float SOUNDVOLUME_LASER	= 0.025f;
}

LaserTurret::~LaserTurret()
{
	if (m_smokeEF != nullptr)
	{
		m_smokeEF->Stop();
	}
	if (m_moveReady == true && m_laserAliveTimer < 0.5f)
	{
		m_laserEF->Stop();
	}
}

bool LaserTurret::Start()
{
	//�^���b�g
	m_turretMR.Init("Assets/ModelData/Turret/LaserTurret.tkm", Normal);
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretMR.Update();

	//�y��
	m_baseMR.Init("Assets/ModelData/Turret/Base.tkm", Normal);
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.SetRotation(m_modelRotation);
	m_baseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_baseMR.Update();
	m_emissionMap.InitFromDDSFile(L"Assets/modelData/Turret/Base2_Emission.DDS");
	m_base2MR.Init("Assets/ModelData/Turret/Base2.tkm", Normal, 0, 0, enModelUpAxisZ, &m_emissionMap);
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.SetRotation(m_modelRotation);
	m_base2MR.SetScale({ 1.0f,1.0f,1.0f });
	m_base2MR.Update();

	//�˒��͈�
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Line.tkm", Dithering);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.25f,1.0f,0.25f });
	m_attackRangeMR.Update();

	//HP��ݒ�
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_hpBarSR.Init("Assets/Sprite/Turret/TurretHP.dds", 30.0f, 30.0f);

	//���[�U�[�̎ˌ�����
	m_forward = { 0.0f,0.0f,-1.0f };
	m_laserPosition = { m_modelPosition.x,m_modelPosition.y + 150.0f,m_modelPosition.z };
	m_modelRotation.Apply(m_forward);

	return true;
}

void LaserTurret::Move()
{
	//�f�o�t�Ɋ|�����Ă�����
	if (m_debuffTimer > 0.0f)
	{
		m_debuffTimer -= g_gameTime->GetFrameDeltaTime();
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 2;
	}
	//����ł�����
	else if (m_hp <= 0.0f)
	{
		m_alive = false;
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 2;
		if (m_smokeEF == nullptr)
		{
			EffectPlaySmoke(m_modelPosition);
		}
		else if (m_smokeEF->IsPlay() == false)
		{
			EffectPlaySmoke(m_modelPosition);
		}
	}
	//�����Ă��ăf�o�t�Ɋ|�����Ă��Ȃ�������
	else
	{
		m_alive = true;
		m_fireRate += g_gameTime->GetFrameDeltaTime();
	}

	//����\�Ȃ�
	if (m_moveReady == true)
	{
		//���˃��[�g
		if (m_fireRate >= FIRERATE)
		{
			m_enemys = FindGOs<EnemyObject>("normal");
			m_laserPosition += m_forward * 200.0f;
			m_laserAliveTimer += g_gameTime->GetFrameDeltaTime();
			//�G�ɓ������Ă�����_���[�W��^����
			for (auto enemys : m_enemys)
			{
				Vector3 difference = enemys->GetPosition() - m_laserPosition;
				if (difference.Length() <= 500.0f)
				{
					enemys->SubEnemyHP(ATTACKPOWER);
				}
			}
			//�G�t�F�N�g���Đ�
			if (m_laserIsPlay == true)
			{
				EffectPlayLaser();
				SoundPlayFire();
				m_laserIsPlay = false;
			}
			//�U���̐������Ԃ��߂����珉����
			if (m_laserAliveTimer >= 0.5f)
			{
				m_laserPosition = { m_modelPosition.x,m_modelPosition.y + 150.0f,m_modelPosition.z };
				m_fireRate = 0.0f;
				m_laserAliveTimer = 0.0f;
				m_laserIsPlay = true;
				m_laserEF->Stop();
			}
			//���[�U�[�̃|�W�V������ݒ�(���[�U�[�����������O�ɌĂяo���Ȃ�)
			m_laserEF->SetPosition(m_laserPosition);
			m_laserEF->SetRotation(m_modelRotation);
		}
	}

	//�X�V����
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.Update();
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.Update();
}

void LaserTurret::HP()
{
	//HP�o�[
	Vector3 position = m_modelPosition;
	position.y += 300.0f;
	g_camera3D->CalcScreenPositionFromWorldPosition(m_hpBarPosition, position);
	m_hpBarSR.SetPosition(Vector3(m_hpBarPosition.x, m_hpBarPosition.y, 0.0f));
	m_hpBarSR.SetIsDisplayRestrictionRightSide(true);
	m_hpBarSR.SetLimitedX(m_hp / m_maxHp);
	m_hpBarSR.Update();
}

void LaserTurret::Update()
{
	Move();
	HP();
}

void LaserTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	m_base2MR.Draw(renderContext);

	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}

	//�_���[�W���󂯂Ă�����
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}

void LaserTurret::EffectPlaySmoke(const Vector3& position)
{
	m_smokeEF = NewGO<EffectEmitter>(0);
	m_smokeEF->Init(enEffectNumber_Smoke);
	m_smokeEF->SetPosition({ position.x,position.y + 100.0f,position.z });
	m_smokeEF->SetScale(Vector3::One * EFFECTSIZE_SMOKE);
	m_smokeEF->Play();
}

void LaserTurret::EffectPlayLaser()
{
	m_laserEF = NewGO<EffectEmitter>(0);
	m_laserEF->Init(enEffectNumber_LaserTurret);
	m_laserEF->SetPosition(m_laserPosition);
	m_laserEF->SetScale(Vector3::One * EFFECTSIZE_LASER);
	m_laserEF->Play();
}

void LaserTurret::SoundPlayFire()
{
	m_fireSE = NewGO<SoundSource>(0);
	m_fireSE->Init(enSoundNumber_LaserTurret);
	m_fireSE->SetVolume(SOUNDVOLUME_LASER);
	m_fireSE->Play(false);
}