#include "stdafx.h"
#include "LeftWindowDelete.h"

#include "LeftWindow.h"
#include "TurretManager.h"

bool LeftWindowDelete::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");
	m_turretManager = FindGO<TurretManager>("turretManager");

	return true;
}

void LeftWindowDelete::Init(InitDeleteTurretSprite initDeleteTurretSprite)
{
	m_initDeleteSpriteNumber = initDeleteTurretSprite;

	switch (m_initDeleteSpriteNumber)
	{
	case enInitDeleteTurretSprite_NormalTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_DualGunTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
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
	case enInitDeleteTurretSprite_GenerationTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_GenerationTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	case enInitDeleteTurretSprite_HealTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_HealTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	default:
		break;
	}
}

void LeftWindowDelete::Init(int number)
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
	case enInitDeleteTurretSprite_HealTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_HealTurret.dds", 720.0f, 720.0f);
		m_spriteRender.Update();
		m_isDraw = true;
		break;
	default:
		break;
	}
}

void LeftWindowDelete::Update()
{
	m_spriteRender.SetPosition(m_position);
	m_spriteRender.Update();
}

void LeftWindowDelete::Render(RenderContext& renderContext)
{
	if (m_isDraw == true && (m_leftWindow->GetOperationState() == enOperationState_Delete_LeftWindow || m_leftWindow->GetOperationState() == enOperationState_DeleteCheck_LeftWindow))
	{
		m_spriteRender.Draw(renderContext);
	}
}