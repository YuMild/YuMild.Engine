#include "stdafx.h"
#include "LeftWindow_Delete.h"

#include "TurretManager.h"

bool LeftWindow_Delete::Start()
{
	m_deleteSpritePosition[0] = { -500.0f,0.0f,0.0f };
	m_deleteSpritePosition[1] = { -415.0f,0.0f,0.0f };
	m_deleteSpritePosition[2] = { -330.0f,0.0f,0.0f };
	m_deleteSpritePosition[3] = { -245.0f,0.0f,0.0f };
	m_deleteSpritePosition[4] = { -500.0f,-100.0f,0.0f };
	m_deleteSpritePosition[5] = { -415.0f,-100.0f,0.0f };
	m_deleteSpritePosition[6] = { -330.0f,-100.0f,0.0f };
	m_deleteSpritePosition[7] = { -245.0f,-100.0f,0.0f };
	m_deleteSpritePosition[8] = { -500.0f,-200.0f,0.0f };
	m_deleteSpritePosition[9] = { -415.0f,-200.0f,0.0f };
	m_deleteSpritePosition[10] = { -330.0f,-200.0f,0.0f };
	m_deleteSpritePosition[11] = { -245.0f,-200.0f,0.0f };
}

void LeftWindow_Delete::Init(InitDeleteTurretSprite initDeleteTurretSprite)
{
	m_isDraw = true;

	switch (m_initDeleteSpriteNumber)
	{
	case enInitDeleteTurretSprite_DualGunTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_DualGunTurret.dds", 720.0f, 720.0f);
		m_spriteRender.SetPosition(m_deleteSpritePosition[m_turretManager->GetTurretSum()]);
		m_spriteRender.Update();
		break;
	case enInitDeleteTurretSprite_LaserTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_LaserTurret.dds", 720.0f, 720.0f);
		m_spriteRender.SetPosition(m_deleteSpritePosition[m_turretManager->GetTurretSum()]);
		m_spriteRender.Update();
		break;
	case enInitDeleteTurretSprite_RocketTurret:
		m_spriteRender.Init("Assets/Sprite/LeftWindow/LeftWindow_RocketTurret.dds", 720.0f, 720.0f);
		m_spriteRender.SetPosition(m_deleteSpritePosition[m_turretManager->GetTurretSum()]);
		m_spriteRender.Update();
		break;
	}
}

void LeftWindow_Delete::Update()
{

}

void LeftWindow_Delete::Render(RenderContext& renderContext)
{
	if (m_isDraw)
	{
		m_spriteRender.Draw(renderContext);
	}
}