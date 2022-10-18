#include "stdafx.h"
#include "DualGunTurret.h"

namespace
{
	Vector3 FIRST_POSITION = { 250.0f,0.0f,190.0f };
}

bool DualGunTurret::Start()
{
	m_position = FIRST_POSITION;

	m_modelRender.Init("Assets/ModelData/Turret/DualGunTurret.tkm", 3);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

	return true;
}

void DualGunTurret::Update()
{
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}