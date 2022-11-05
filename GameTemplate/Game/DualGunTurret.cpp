#include "stdafx.h"
#include "DualGunTurret.h"

#include "LeftWindow.h"

bool DualGunTurret::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");

	m_modelRender.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowRecieveAndDrop,true);
	m_modelRender.SetPosition(m_modelPosition);
	m_modelRender.SetRotation(m_modelRotation);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

	m_spriteRender.Init("Assets/sprite/LeftWindow/LeftWindow_DualGunTurret.dds", 720.0f, 720.0f);

	return true;
}

void DualGunTurret::Update()
{
	m_modelRender.SetPosition(m_modelPosition);
	m_modelRender.SetRotation(m_modelRotation);
	m_modelRender.Update();

	m_spriteRender.SetPosition(m_spritePosition);
	m_spriteRender.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);

	if (m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow)
	{
		m_spriteRender.Draw(renderContext);
	}
}