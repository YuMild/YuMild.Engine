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
	//初期化
	m_position = CONTAINER_POSITION;
	m_scale = CONTAINER_SCALE;

	//モデル
	m_containerMR.Init("Assets/ModelData/Stage/Container.tkm");
	m_containerMR.SetPosition(m_position);
	m_containerMR.SetScale(Vector3::One * m_scale);
	m_containerMR.Update();

	//ターゲット
	m_target = CONTAINER_TARGET;

	return true;
}

void Container::Move()
{
	//目的地までのベクトル
	Vector3 difference = m_target - m_position;

	//目的地に着いたら
	if (difference.Length() >= 10.0f)
	{
		//移動
		Vector3 moveSpeed = m_target - m_position;
		moveSpeed.Normalize();
		m_position += moveSpeed * CONTAINER_MOVESPEED;

		//更新処理
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