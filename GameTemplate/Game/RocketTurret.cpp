#include "stdafx.h"
#include "RocketTurret.h"

#include "LeftWindow.h"

bool RocketTurret::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	m_modelRender.Init("Assets/ModelData/Turret/RocketTurret.tkm", ShadowRecieveAndDrop, true);
	m_modelRender.SetPosition(m_modelPosition);
	m_modelRender.SetRotation(m_modelRotation);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

	return true;
}

void RocketTurret::Update()
{
	m_modelRender.SetPosition(m_modelPosition);
	m_modelRender.SetRotation(m_modelRotation);
	m_modelRender.Update();

	m_spriteRender.SetPosition(m_spritePosition);
	m_spriteRender.Update();
}

void RocketTurret::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}