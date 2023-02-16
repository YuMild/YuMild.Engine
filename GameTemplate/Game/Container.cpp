#include "stdafx.h"
#include "Container.h"

namespace
{
	const Vector3	CONTAINER_POSITION = { -8000.0f,500.0f,-8000.0f };
	const float		CONTAINER_SCALE = 50.0f;
	const Vector3	CONTAINER_TARGET = { 0.0f,500.0f,-8000.0f };
	const float		CONTAINER_MOVESPEED = 50.0f;
}

Container::~Container()
{

}

bool Container::Start()
{
	//������
	m_position = CONTAINER_POSITION;
	m_scale = CONTAINER_SCALE;

	//���f��
	m_containerMR.Init("Assets/ModelData/Stage/Container.tkm");
	m_containerMR.SetPosition(m_position);
	m_containerMR.SetScale(Vector3::One * m_scale);
	m_containerMR.Update();

	//�^�[�Q�b�g
	m_target = CONTAINER_TARGET;

	return true;
}

void Container::Move()
{
	//�ړI�n�܂ł̃x�N�g��
	Vector3 difference = m_target - m_position;

	//�ړI�n�ɒ�������
	if (difference.Length() >= 10.0f)
	{
		//�ړ�
		Vector3 moveSpeed = m_target - m_position;
		moveSpeed.Normalize();
		m_position += moveSpeed * CONTAINER_MOVESPEED;

		//�X�V����
		m_containerMR.SetPosition(m_position);
		m_containerMR.Update();
	}
}

void Container::Update()
{
	Move();
}

void Container::Render(RenderContext& renderContext)
{
	m_containerMR.Draw(renderContext);
}