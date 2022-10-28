#include "stdafx.h"
#include "TurretManager.h"

#include "DualGunTurret.h"
#include "LaserTurret.h"

void TurretManager::DualGunTurretMake()
{
	auto* turret = NewGO<DualGunTurret>(0, "dualGunTurret");
	turret->SetPosition({ 200.0f,0.0f,190.0f });
	m_turrets.push_back(turret);
	m_turretsSum++;
}

void TurretManager::LaserTurretMake()
{
	auto* turret = NewGO<LaserTurret>(0, "laserTurret");
	turret->SetPosition({ 1000.0f,0.0f,190.0f });
	m_turrets.push_back(turret);
	m_turretsSum++;
}

void TurretManager::Init(Turrets enturret)
{
	switch(enturret)
	{
	case enTurretDualGunTurret:
		DualGunTurretMake();
		break;

	case enTurretLaserTurret:
		LaserTurretMake();
		break;

	default:
		break;
	}
}

void TurretManager::Update()
{
	if (g_pad[0]->IsTrigger(enButtonSelect) && m_turretsSum != 0)
	{
		std::vector<IGameObject*>::iterator it;
		it = std::find(
			m_turrets.begin(),
			m_turrets.end(),
			m_turrets[m_turretsSum-1]
		);
		DeleteGO(m_turrets[m_turretsSum - 1]);
		m_turrets.erase(it);
		m_turretsSum--;
	}
}