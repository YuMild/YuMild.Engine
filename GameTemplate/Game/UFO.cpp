#include "stdafx.h"
#include "UFO.h"

#include "GameCamera.h"
#include "GameOver.h"

#include "SpawnManager.h"
#include "TurretManager.h"

namespace
{
	//���f���̏����l
	Vector3 DEFAULT_POSITION		= { 0.0f,200.0f,-9500.0f };
	float	DEFAULT_SCALE			= 2.95f;

	//�|�C���g�|�W�V����
	Vector3 POINT_1_POSITION		= { 0.0f,0.0f,-5900.0f };
	Vector3 POINT_2_POSITION		= { -2750.0f,0.0f,-5900.0f };
	Vector3 POINT_3_POSITION		= { -2750.0f,0.0f,-3150.0f };
	Vector3 POINT_4_POSITION		= { 2750.0f,0.0f,-3150.0f };
	Vector3 POINT_5_POSITION		= { 2750.0f,0.0f,-2000.0f };
	Vector3 POINT_6_POSITION		= { 0.0f,0.0f,-2000.0f };
	Vector3 POINT_7_POSITION		= { 0.0f,0.0f,0.0f };

	//�p�����[�^�[
	float DEFAULT_MOVE_SPEED		= 15.0f;
	float DEFAULT_ROTATION_SPEED	= 1.5f;
}

UFO::~UFO()
{

}

bool UFO::Start()
{
	//FindGO
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_gameOver = FindGO<GameOver>("gameOver");
	m_spawnManager = FindGO<SpawnManager>("spawnManager");
	m_turretManager = FindGO<TurretManager>("turretManager");
	
	m_position = DEFAULT_POSITION;

	//���f��
	m_emissionMap.InitFromDDSFile(L"Assets/modelData/Enemy/UFO_Blue_Emission.DDS");
	m_modelRender.Init("Assets/modelData/Enemy/UFO_Blue.tkm", Normal, 0, 0, enModelUpAxisZ, &m_emissionMap);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	//HP
	m_hp = m_spawnManager->GetDefaultHP_UFO();
	m_maxHp = m_spawnManager->GetDefaultHP_UFO();
	m_hpBarSR.Init("Assets/Sprite/Enemy/EnemyHP.dds",30.0f,30.0f);
	
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

	return true;
}

void UFO::Move()
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
			m_gameCamera->SetCameraShake();
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
	//�S������Ă��Ȃ�������
	if (m_bindTimer <= 0.0f)
	{
		Vector3 moveSpeed = m_target - m_position;
		moveSpeed.Normalize();
		//�ړ�
		m_position += moveSpeed * DEFAULT_MOVE_SPEED;
		//��]��������
		m_rotation.AddRotationDegY(DEFAULT_ROTATION_SPEED);
	}
	//�S������Ă�����
	else
	{
		m_bindTimer -= g_gameTime->GetFrameDeltaTime();
	}

	//���X�ɑ傫������
	if (m_scale <= DEFAULT_SCALE)
	{
		m_scale += 0.25f;
	}

	//�X�V����
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(Vector3::One * m_scale);
	m_modelRender.Update();
}

void UFO::HP()
{
	//HP�o�[
	Vector3 position = m_position;
	position.y += 300.0f;
	g_camera3D->CalcScreenPositionFromWorldPosition(m_hpBarPosition, position);
	m_hpBarSR.SetPosition(Vector3(m_hpBarPosition.x, m_hpBarPosition.y, 0.0f));
	m_hpBarSR.SetIsDisplayRestrictionRightSide(true);
	m_hpBarSR.SetLimitedX(m_hp / m_spawnManager->GetDefaultHP_UFO());
	m_hpBarSR.Update();
}

void UFO::Update()
{
	Move();
	HP();
}

void UFO::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);

	//�_���[�W���󂯂Ă�����
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}