#include "stdafx.h"
#include "Container.h"

#include "Game.h"

namespace
{
	//���f��
	//�V�b�v
	const Vector3	CONTAINERSHIP_POSITION		= { -10000.0f,2700.0f,-9500.0f };
	const float		CONTAINERSHIP_SCALE			= 150.0f;
	const Vector3	CONTAINERSHIP_TARGET		= { 10.0f,2700.0f,-9500.0f };
	const float		CONTAINERSHIP_MOVESPEED		= 105.0f;
	//�R���e�i
	const float		CONTAINER_SCALE				= 25.0f;
	//�L�����v
	const float		CAMP_SCALE					= 13.0f;

	//�G�t�F�N�g
	const float		EFFECT_SIZE					= 500.0f;

	//�J����
	const Vector3	CAMERA_POSITION				= { 0.0f,1000.0f,-4000.0f };
}

Container::~Container()
{

}

bool Container::Start()
{
	//FindGO
	m_game = FindGO<Game>("game");

	//������
	m_modelPosition = CONTAINERSHIP_POSITION;

	//���f��
	//�V�b�v
	m_containerShipMR.Init("Assets/ModelData/Stage/ContainerShip.tkm");
	m_containerShipMR.SetPosition(m_modelPosition);
	m_containerShipMR.SetScale(Vector3::One * CONTAINERSHIP_SCALE);
	m_containerShipMR.Update();
	//�R���e�i
	m_containerMR.Init("Assets/ModelData/Stage/Container.tkm");
	m_containerMR.SetPosition({ m_modelPosition.x,m_modelPosition.y - 2000.0f,m_modelPosition.z });
	m_containerMR.SetScale(Vector3::One * CONTAINER_SCALE);
	m_containerMR.Update();
	//�h�A
	m_containerDoorMR.Init("Assets/ModelData/Stage/ContainerDoor.tkm");
	m_containerDoorMR.SetPosition({ m_modelPosition.x,m_modelPosition.y - 300.0f,m_modelPosition.z });
	m_containerDoorMR.SetScale(Vector3::One * CONTAINER_SCALE);
	m_containerDoorMR.Update();
	m_campEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/Camp_Emission.DDS");
	//�L�����v
	m_campMR.Init("Assets/ModelData/Stage/Camp.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_campEmissionMap);
	m_campMR.SetPosition({ m_modelPosition.x,m_modelPosition.y - 2700.0f,m_modelPosition.z });
	m_campMR.SetScale(Vector3::One * CAMP_SCALE);
	m_campMR.Update();

	//MoveSpeed
	m_moveSpeed = CONTAINERSHIP_MOVESPEED;

	//�^�[�Q�b�g
	m_target = CONTAINERSHIP_TARGET;

	//�T�E���h�̍Đ�
	SoundPlayContainerShipMove();

	m_fontRenderX.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderX.SetScale(1.0f);
	m_fontRenderX.SetPivot(1.0f, 0.5f);
	m_fontRenderX.SetPosition({ 700.0f,450.0f,0.0f });

	m_fontRenderY.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderY.SetScale(1.0f);
	m_fontRenderY.SetPivot(1.0f, 0.5f);
	m_fontRenderY.SetPosition({ 700.0f,400.0f,0.0f });

	m_fontRenderZ.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_fontRenderZ.SetScale(1.0f);
	m_fontRenderZ.SetPivot(1.0f, 0.5f);
	m_fontRenderZ.SetPosition({ 700.0f,350.0f,0.0f });

	m_doorRotationFR.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_doorRotationFR.SetScale(1.0f);
	m_doorRotationFR.SetPivot(1.0f, 0.5f);
	m_doorRotationFR.SetPosition({ 700.0f,300.0f,0.0f });

	return true;
}

void Container::Move()
{
	//�ړI�n�܂ł̃x�N�g��
	Vector3 difference = m_target - m_modelPosition;

	//�ړI�n�ɒ����܂�
	if (difference.Length() >= 10.0f)
	{
		//�X�L�b�v
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//���f�����ړ�
			m_modelPosition = { -0.0f,2700.0f,-9500.0f };
			m_containerShipMR.SetPosition(m_modelPosition);
			m_containerShipMR.Update();
			//�X�e�[�g���ڍs
			m_moveTimer = 4.0f;
			//�h�A����]
			m_doorRotation.SetRotationX(1.5f);
			m_containerDoorMR.SetRotation(m_doorRotation);
			m_containerDoorMR.Update();
			//�T�E���h���X�g�b�v
			if (m_containerShipMoveSE != nullptr && m_containerShipMoveSE->IsPlaying() != false)
			{
				m_containerShipMoveSE->Stop();
			}
		}

		//�ړ�
		Vector3 moveSpeed = m_target - m_modelPosition;
		moveSpeed.Normalize();
		m_modelPosition += moveSpeed * m_moveSpeed;
		//���X�Ɍ���
		if (m_moveSpeed >= 1.0f)
		{
			m_moveSpeed *= 0.99f;
		}

		//�J�����ړ�
		m_cameraPosition = CAMERA_POSITION;
		g_camera3D->SetPosition(m_cameraPosition);
		m_cameraTarget = { m_modelPosition.x,m_modelPosition.y - 500.0f,m_modelPosition.z };
		g_camera3D->SetTarget(m_cameraTarget);
		g_camera3D->Update();

		//�X�V����
		//�V�b�v
		m_containerShipMR.SetPosition(m_modelPosition);
		m_containerShipMR.Update();
		//�R���e�i
		m_containerMR.SetPosition({ m_modelPosition.x,m_modelPosition.y - 3000.0f,m_modelPosition.z });
		m_containerMR.Update();
		//�h�A
		m_containerDoorMR.SetPosition({ m_modelPosition.x,m_modelPosition.y - 1200.0f,m_modelPosition.z + 1000.0f });
		m_containerDoorMR.Update();
		//�L�����v
		m_campMR.SetPosition({ m_modelPosition.x,m_modelPosition.y - 2700.0f,m_modelPosition.z });
		m_campMR.Update();
	}

	//�h�A�̊J�����o
	else if (difference.Length() < 500.0f && m_moveTimer < 4.0f)
	{
		if (m_doorRotationValue < 1.5f)
		{
			m_doorRotationValue += 0.01f;
			m_doorRotation.SetRotationX(-m_doorRotationValue);
			m_containerDoorMR.SetRotation(m_doorRotation);
			m_containerDoorMR.Update();
		}
		if (m_containerDoorSE == nullptr)
		{
			SoundPlayContainerDoor();
		}
		m_moveTimer += g_gameTime->GetFrameDeltaTime();
	}

	//�h�A���J���I�������Q�[���J�n
	else if (m_moveTimer >= 4.0f)
	{
		m_game->SetGameState(enGameState_InGame);
	}

	//�T�E���h�̃t�F�[�h�C��
	if (m_soundSize <= 0.15f && m_containerShipMoveSE != nullptr)
	{
		m_soundSize += 0.001f;
		m_containerShipMoveSE->SetVolume(m_soundSize);
	}
}

void Container::Update()
{
	Move();

	wchar_t X[256];
	swprintf_s(X, 256, L"%04d", int(m_modelPosition.x));
	m_fontRenderX.SetText(X);
	wchar_t Y[256];
	swprintf_s(Y, 256, L"%04d", int(m_modelPosition.y));
	m_fontRenderY.SetText(Y);
	wchar_t Z[256];
	swprintf_s(Z, 256, L"%04d", int(m_modelPosition.z));
	m_fontRenderZ.SetText(Z);
	wchar_t R[256];
	swprintf_s(R, 256, L"%04d", int(m_doorRotationValue * 100.0f));
	m_doorRotationFR.SetText(R);
}

void Container::Render(RenderContext& renderContext)
{
	//���f��
	m_containerShipMR.Draw(renderContext);
	m_containerMR.Draw(renderContext);
	m_containerDoorMR.Draw(renderContext);
	m_campMR.Draw(renderContext);

	//�t�H���g
#ifdef K2_DEBUG
	m_fontRenderX.Draw(renderContext);
	m_fontRenderY.Draw(renderContext);
	m_fontRenderZ.Draw(renderContext);
	m_doorRotationFR.Draw(renderContext);
#endif
}

void Container::SoundPlayContainerDoor()
{
	m_containerDoorSE = NewGO<SoundSource>(0);
	m_containerDoorSE->Init(enSoundNumber_ContainerDoor);
	m_containerDoorSE->SetVolume(0.15f);
	m_containerDoorSE->Play(false);
}

void Container::SoundPlayContainerShipMove()
{
	m_containerShipMoveSE = NewGO<SoundSource>(0);
	m_containerShipMoveSE->Init(enSoundNumber_ContainerShipMove);
	m_containerShipMoveSE->SetVolume(m_soundSize);
	m_containerShipMoveSE->Play(false);
}