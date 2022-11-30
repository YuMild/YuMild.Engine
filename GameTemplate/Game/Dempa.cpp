#include "stdafx.h"
#include "Dempa.h"

#include "GameOver.h"

#include "SpawnManager.h"
#include "TurretManager.h"

namespace
{
	//���f���̏����l
	Vector3 DEFAULT_POSITION = { 0.0f,0.0f,-8000.0f };
	Vector3 DEFAULT_SCALE = { 2.95f,2.95f,2.95f };
	float DEFAULT_ROTATION_Y = 0.0f;

	//�|�C���g�|�W�V����
	Vector3 POINT_1_POSITION = { 0.0f,0.0f,-5900.0f };
	Vector3 POINT_2_POSITION = { -2750.0f,0.0f,-5900.0f };
	Vector3 POINT_3_POSITION = { -2750.0f,0.0f,-3150.0f };
	Vector3 POINT_4_POSITION = { 2750.0f,0.0f,-3150.0f };
	Vector3 POINT_5_POSITION = { 2750.0f,0.0f,-2000.0f };
	Vector3 POINT_6_POSITION = { 0.0f,0.0f,-2000.0f };
	Vector3 POINT_7_POSITION = { 0.0f,0.0f,0.0f };

	//�p�����[�^�[
	float DEFAULT_MOVE_SPEED = 15.0f;
	float DEFAULT_ROTATION_SPEED = 1.5f;
}

Dempa::Dempa()
{

}

Dempa::~Dempa()
{
	//�G�t�F�N�g���~�߂�
	m_dempaAttackEF->Stop();
}

bool Dempa::Start()
{
	//�R���W�����̃��C���[�t���[���\��
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//FindGO
	m_gameOver = FindGO<GameOver>("gameOver");
	m_spawnManager = FindGO<SpawnManager>("spawnManager");
	m_turretManager = FindGO<TurretManager>("turretManager");

	//���f��
	m_modelRender.Init("Assets/modelData/Enemy/UFO_Yellow.tkm", ShadowRecieveAndDrop);
	m_position = DEFAULT_POSITION;
	m_modelRender.SetPosition(m_position);
	m_rotation.SetRotationDegY(DEFAULT_ROTATION_Y);
	m_modelRender.SetRotation(m_rotation);
	m_scale = DEFAULT_SCALE;
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//�R���W����
	m_characterController.Init(300.0f, 1.0f, m_position);

	//HP
	m_hp = m_spawnManager->GetDefaultHP_UFO();
	m_hpMax = m_spawnManager->GetDefaultHP_UFO();
	m_hpBarSR.Init("Assets/Sprite/Enemy/EnemyHP.dds", 30.0f, 30.0f);

	//�p�X�ړ�
	m_pointList.push_back({ POINT_1_POSITION });     //1�Ԗڂ̃|�C���g
	m_pointList.push_back({ POINT_2_POSITION });     //2�Ԗڂ̃|�C���g
	m_pointList.push_back({ POINT_3_POSITION });     //3�Ԗڂ̃|�C���g
	m_pointList.push_back({ POINT_4_POSITION });     //4�Ԗڂ̃|�C���g
	m_pointList.push_back({ POINT_5_POSITION });     //5�Ԗڂ̃|�C���g
	m_pointList.push_back({ POINT_6_POSITION });     //6�Ԗڂ̃|�C���g
	m_pointList.push_back({ POINT_7_POSITION });     //7�Ԗڂ̃|�C���g
	m_pointNum = 0;
	m_target = m_pointList[m_pointNum];

	//�G�t�F�N�g�𐶐�
	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/effect/DempaAttack.efk");
	m_dempaAttackEF = NewGO<EffectEmitter>(0);
	m_dempaAttackEF->Init(4);
	m_dempaAttackEF->SetPosition({ m_position.x,m_position.y + 100.0f,m_position.z });
	m_dempaAttackEF->SetScale(Vector3::One * 500.0f);
	m_dempaAttackEF->Play();

	return true;
}

void Dempa::Attack()
{
	m_dempaAttackEF->SetPosition({ m_position.x,m_position.y + 50.0f,m_position.z });

	//�˒����Ƀ^���b�g��������f�o�t���|����
	m_turrets = FindGOs<TurretObject>("turret");
	{
		for (auto lockOnObject : m_turrets)
		{
			Vector3 difference = lockOnObject->GetModelPosition() - m_position;
			//�U���͈͓��Ȃ�
			if (difference.Length() < 1000.0f)
			{
				lockOnObject->SetDebuff();
			}
		}
	}
}

void Dempa::Move()
{
	//�ړI�n�܂ł̃x�N�g��
	Vector3 difference = m_target - m_position;

	//�ړI�n�ɒ�������
	if (difference.Length() <= 10.0f)
	{
		//�ړI�n��ς���
		if (m_pointNum < 6)
		{
			m_pointNum += 1;
			m_target = m_pointList[m_pointNum];
		}
		//���_�ɒH�蒅������
		else
		{
			m_spawnManager->EffectPlayExplosion(m_position);
			m_spawnManager->SoundPlayExplosion();
			m_gameOver->SubHP();
			m_dempaAttackEF->Stop();
			DeleteGO(this);
			return;
		}
	}

	//HP��0�ɂȂ�����
	if (m_hp <= 0.0f)
	{
		m_spawnManager->EffectPlayExplosion(m_position);
		m_spawnManager->SoundPlayExplosion();
		DeleteGO(this);
	}

	//�ړ�
	Vector3 moveSpeed = m_target - m_position;
	moveSpeed.Normalize();
	moveSpeed *= DEFAULT_MOVE_SPEED;
	m_position = m_characterController.Execute(moveSpeed, 1.0f);

	//��]��������
	m_rotation.AddRotationDegY(DEFAULT_ROTATION_SPEED);

	//�X�V����
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}

void Dempa::HP()
{
	//HP�o�[
	Vector3 position = m_position;
	position.y += 300.0f;
	g_camera3D->CalcScreenPositionFromWorldPosition(m_hpBarPosition, position);
	m_hpBarSR.SetPosition(Vector3(m_hpBarPosition.x, m_hpBarPosition.y, 0.0f));
	m_hpBarSR.SetIsDisplayRestrictionRightSide(true);
	m_hpBarSR.SetLimitedX(m_hp / 100.0f);
	m_hpBarSR.Update();
}

void Dempa::Update()
{
	Attack();
	Move();
	HP();
}

void Dempa::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);

	//�_���[�W���󂯂Ă�����
	if (m_hp <= m_hpMax - 1.0f)
	{
		m_hpBarSR.Draw(renderContext);
	}
}