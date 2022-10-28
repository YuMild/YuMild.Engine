#pragma once

enum Turrets
{
	enTurretDualGunTurret,
	enTurretLaserTurret,
	enTurretLocketTurret,
	en3,
	en4,
	en5,
	en6,
	en7,
	en8,
	en9,
	en10,
	en11
};

class TurretManager : public IGameObject
{
public:

	void DualGunTurretMake();
	void LaserTurretMake();
	void Init(Turrets enturret);

	void Update();

private:

	std::vector<IGameObject*>m_turrets;

	int m_turretsSum;
};