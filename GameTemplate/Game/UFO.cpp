#include "stdafx.h"
#include "UFO.h"

namespace
{
	//�����l
	Vector3 FIRST_POSITION = { 0.0f,0.0f,-9600.0f };
	float FIRST_ROTATION_Y = 0.0f;

	//�|�C���g�|�W�V����
	Vector3 POINT_1_POSITION = { 0.0f,0.0f,-6700.0f };
	Vector3 POINT_2_POSITION = { -2800.0f,0.0f,-6700.0f };
	Vector3 POINT_3_POSITION = { -2800.0f,0.0f,-4000.0f };
	Vector3 POINT_4_POSITION = { 2800.0f,0.0f,-4000.0f };
	Vector3 POINT_5_POSITION = { 2800.0f,0.0f,-2800.0f };
	Vector3 POINT_6_POSITION = { 0.0f,0.0f,-2800.0f };
	Vector3 POINT_7_POSITION = { 0.0f,0.0f,0.0f };

	float MOVE_SPEED = 100.0f;
}

UFO::UFO()
{

}

UFO::~UFO()
{

}

bool UFO::Start()
{
	m_position = FIRST_POSITION;
	m_rotation.SetRotationDegY(FIRST_ROTATION_Y);

	m_modelRender.Init("Assets/modelData/Enemy/UFO_Blue.tkm", ShadowRecieveAndDrop);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

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
	Vector3 difference = m_target - m_position;

	if (difference.Length() <= 50.0f)
	{
		if (m_pointNum < 6)
		{
			m_pointNum += 1;
			m_target = m_pointList[m_pointNum];
		}
		else
		{
			DeleteGO(this);
			return;
		}
	}

	Vector3 moveSpeed = m_target - m_position;
	moveSpeed.Normalize();
	moveSpeed *= MOVE_SPEED;
	m_position += moveSpeed;

	//��]��������
	m_rotation.AddRotationDegY(1.0f);

	//�X�V����
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}

void UFO::Update()
{
	Move();
}

void UFO::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}