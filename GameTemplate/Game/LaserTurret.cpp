#include "stdafx.h"
#include "LaserTurret.h"

namespace
{
	Vector3 FIRST_POSITION = { 200.0f,0.0f,190.0f };
	float FIRST_ROTATION_Y = 0.0f;
}

bool LaserTurret::Start()
{
	m_rotation.SetRotationDegY(FIRST_ROTATION_Y);

	m_modelRender.Init("Assets/ModelData/Turret/LaserTurret.tkm", ShadowRecieveAndDrop, true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

	return true;
}

void LaserTurret::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}

void LaserTurret::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}