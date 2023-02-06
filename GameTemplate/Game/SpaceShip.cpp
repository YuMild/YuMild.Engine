#include "stdafx.h"
#include "SpaceShip.h"

#include "GameCamera.h"
#include "GameOver.h"
#include "Stage.h"

#include "SpawnManager.h"
#include "TurretManager.h"

namespace
{
	//���f���̏����l
	Vector3 DEFAULT_POSITION = { 0.0f,1000.0f,-8000.0f };
	Vector3 DEFAULT_SCALE = { 3.0f,3.0f,3.0f };
	Vector3 DEFAULT_TARGET = { 0.0f,1000.0f,-0.0f };

	//�p�����[�^�[
	float DEFAULT_MOVE_SPEED = 3.0f;
	float DEFAULT_ROTATION_SPEED = 1.5f;
}

SpaceShip::~SpaceShip()
{
	m_gameCamera->SetCameraState(enCameraState_Normal);
	m_stage->SetNormalBGM();
}

bool SpaceShip::Start()
{
	//FindGO
	m_gameOver = FindGO<GameOver>("gameOver");
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_stage = FindGO<Stage>("stage");
	m_spawnManager = FindGO<SpawnManager>("spawnManager");
	m_turretManager = FindGO<TurretManager>("turretManager");

	m_position = DEFAULT_POSITION;
	m_scale = DEFAULT_SCALE;

	//���f��
	m_emissionMap.InitFromDDSFile(L"Assets/modelData/Enemy/SpaceShip_Emission.DDS");
	m_modelRender.Init("Assets/modelData/Enemy/SpaceShip.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_emissionMap);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//HP
	m_hp = m_spawnManager->GetDefaultHP_SpaceShip();
	m_maxHp = m_spawnManager->GetDefaultHP_SpaceShip();
	m_hpBarSR.Init("Assets/Sprite/Enemy/EnemyHP.dds", 30.0f, 30.0f);

	//�{�X�p�̎��_�ɕύX
	m_gameCamera->SetCameraState(enCameraState_SpaceShip);
	m_stage->SetBossBGM();

	return true;
}

void SpaceShip::Move()
{
	//�ړI�n�܂ł̃x�N�g��
	Vector3 difference = DEFAULT_TARGET - m_position;

	//�ړI�n�ɒ�������
	if (difference.Length() <= 10.0f)
	{
		m_spawnManager->EffectPlayExplosion(m_position);
		m_spawnManager->SoundPlayExplosion();
		m_gameOver->SubHP();
		m_gameCamera->SetCameraShake();
		DeleteGO(this);
	}

	//HP��0�ɂȂ�����
	if (m_hp <= 0.0f)
	{
		m_spawnManager->EffectPlayExplosion(m_position);
		m_spawnManager->SoundPlayExplosion();
		DeleteGO(this);
	}

	//�ړ�
	Vector3 moveSpeed = difference;
	moveSpeed.Normalize();
	moveSpeed *= DEFAULT_MOVE_SPEED;
	m_position += moveSpeed;

	//�X�V����
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}

void SpaceShip::HP()
{
	//HP�o�[
	Vector3 position = m_position;
	position.y += 500.0f;
	g_camera3D->CalcScreenPositionFromWorldPosition(m_hpBarPosition, position);
	m_hpBarSR.SetPosition(Vector3(m_hpBarPosition.x, m_hpBarPosition.y, 0.0f));
	m_hpBarSR.SetIsDisplayRestrictionRightSide(true);
	m_hpBarSR.SetLimitedX(m_hp / m_spawnManager->GetDefaultHP_SpaceShip());
	m_hpBarSR.Update();
}

void SpaceShip::Update()
{
	Move();
	HP();
}

void SpaceShip::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);

	//�_���[�W���󂯂Ă�����
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}