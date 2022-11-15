#include "stdafx.h"
#include "DualGunTurret.h"

#include "LeftWindow.h"

#include "TurretManager.h"

namespace
{
	float FIRERATE = 0.1f;
}

bool DualGunTurret::Start()
{
	m_leftWindow = FindGO<LeftWindow>("leftWindow");
	m_turretManager = FindGO<TurretManager>("turretManager");

	m_modelRender.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowRecieveAndDrop,true);
	m_modelRender.SetPosition(m_modelPosition);
	m_modelRender.SetRotation(m_modelRotation);
	m_modelRender.SetScale({ 1.0f,1.0f,1.0f });
	m_modelRender.Update();

	return true;
}

void DualGunTurret::Attack()
{
	m_fireRate += g_gameTime->GetFrameDeltaTime();
	//射程より長ければOK
	m_difference = { 10000.0f,10000.0f,10000.0f };
	//ロックオンしたか否か
	m_enemys = FindGOs<EnemyObject>("ufo");
	for (auto lockOnObject : m_enemys)
	{
		//全ての敵との距離を測る
		Vector3 difference = lockOnObject->GetPosition() - m_modelPosition;
		//射程内で且つ一番近かったら
		if (difference.Length() >= 1000.0f)
		{
			continue;
		}
		if (difference.Length() < m_difference.Length())
		{
			//m_lockOnPosition = lockOnObject->GetPosition();
			m_difference = difference;
			if (m_fireRate >= FIRERATE)
			{
				lockOnObject->MulScale();
				m_fireRate = 0.0f;
			}
		}
	}

	//正規化
	m_difference.Normalize();
}

void DualGunTurret::Update()
{
	Attack();

	m_modelRender.SetPosition(m_modelPosition);
	m_modelRender.SetRotation(m_modelRotation);
	m_modelRender.Update();

	m_spriteRender.SetPosition(m_spritePosition);
	m_spriteRender.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}