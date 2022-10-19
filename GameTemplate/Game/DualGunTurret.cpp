#include "stdafx.h"
#include "DualGunTurret.h"

namespace
{
	Vector3 FIRST_POSITION = { 200.0f,0.0f,190.0f };
	float FIRST_ROTATION_Y = 0.0f;
}

bool DualGunTurret::Start()
{
	m_position = FIRST_POSITION;
	m_rotation.SetRotationDegY(FIRST_ROTATION_Y);

	m_modelRender.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowRecieveAndDrop,true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

	return true;
}

void DualGunTurret::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}