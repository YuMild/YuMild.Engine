#include "stdafx.h"
#include "LeftWindow_Delete.h"

#include "LeftWindow.h"
#include "TurretManager.h"

bool LeftWindow_Delete::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");
	m_turretManager = FindGO<TurretManager>("turretManager");

	return true;
}

void LeftWindow_Delete::Init(InitDeleteTurretSprite initDeleteTurretSprite)
{
	m_initDeleteSpriteNumber = initDeleteTurretSprite;

	switch (m_initDeleteSpriteNumber)
	{
	case enInitDeleteTurretSprite_DualGunTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_DualGunTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	case enInitDeleteTurretSprite_LaserTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_LaserTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	case enInitDeleteTurretSprite_RocketTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_RocketTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	default:
		break;
	}
}

void LeftWindow_Delete::Init(int number)
{
	m_initDeleteSpriteNumber = number;

	switch (m_initDeleteSpriteNumber)
	{
	case enInitDeleteTurretSprite_DualGunTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_DualGunTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	case enInitDeleteTurretSprite_LaserTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_LaserTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	case enInitDeleteTurretSprite_RocketTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_RocketTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	default:
		break;
	}
}

void LeftWindow_Delete::Update()
{
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.Update();
}

void LeftWindow_Delete::Render(RenderContext& renderContext)
{
	if (m_isDraw == true && m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow)
	{
		m_spriteRender.Draw(renderContext);
	}
}