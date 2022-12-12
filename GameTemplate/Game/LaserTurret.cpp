#include "stdafx.h"
#include "LaserTurret.h"

namespace
{
	float FIRERATE = 2.0f;
	float ATTACKPOWER = 30.0f;
}

LaserTurret::LaserTurret()
{

}

LaserTurret::~LaserTurret()
{
	if (m_moveReady == true && m_laserAliveTimer < 0.5f)
	{
		m_laserEF->Stop();
	}
}

bool LaserTurret::Start()
{
	//�^���b�g
	m_turretMR.Init("Assets/ModelData/Turret/LaserTurret.tkm", ShadowRecieveAndDrop, true);
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
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Line.tkm", Dithering, true);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.25f,1.0f,0.25f });
	m_attackRangeMR.Update();

	//�G�t�F�N�g
	EffectEngine::GetInstance()->ResistEffect(5, u"Assets/Effect/LaserTurret.efk");

	//�����̐���
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/LaserTurret.wav");

	//���[�U�[�̎ˌ�����
	m_forward = { 0.0f,0.0f,-1.0f };
	m_laserPosition = { m_modelPosition.x,m_modelPosition.y + 150.0f,m_modelPosition.z };
	m_modelRotation.Apply(m_forward);

	return true;
}

void LaserTurret::Move()
{
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
					enemys->SubHP(ATTACKPOWER);
				}
			}
			//�G�t�F�N�g���Đ�
			if (m_laserIsPlay == true)
			{
				m_laserEF = NewGO<EffectEmitter>(0);
				m_laserEF->Init(5);
				m_laserEF->SetPosition(m_laserPosition);
				m_laserEF->SetScale(Vector3::One * 200.0f);
				m_laserEF->Play();
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
}

void LaserTurret::Update()
{
	Move();

	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.Update();
}

void LaserTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}
}