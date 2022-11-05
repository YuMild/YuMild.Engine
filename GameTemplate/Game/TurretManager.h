#pragma once

class LeftWindow;

class DualGunTurret;
class LaserTurret;
class RocketTurret;

enum Turret
{
	enTurret_DualGunTurret,
	enTurret_LaserTurret,
	enTurret_RocketTurret,
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

enum SpritePosition
{
	enSpritePosition_DuarGunTurret,
	enSpritePosition_LaserTurret,
	enSpritePosition_RocketTurret
};

class TurretManager : public IGameObject
{
public:

	bool Start();
	void Update();

	/// <summary>
	/// ƒ^ƒŒƒbƒg‚ğì¬
	/// </summary>
	/// <param name="enturret"></param>
	void Init(Turret enturret);

private:

	void StateManager();
	void MakeDualGunTurret();
	void MakeLaserTurret();
	void MakeRocketTurret();

	std::vector<IGameObject*>		m_turrets;

	LeftWindow*						m_leftWindow;
	
	DualGunTurret*					m_dualGunTurret;
	LaserTurret*					m_laserTurret;
	RocketTurret*					m_rocketTurret;

	Vector3							m_cursorPosition;

	Vector3							m_spritePosition[12];

	bool							m_isModelNewGO = false;
	bool							m_isGorstModelNewGO = false;

	int								m_deleteNumber = -1;
	int								m_turretType = 0;
	int								m_turretsSum = 0;

	float							m_rotation = 0.0f;
};