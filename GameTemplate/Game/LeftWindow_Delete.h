#pragma once

class TurretManager;

enum InitDeleteTurretSprite
{
	enInitDeleteTurretSprite_DualGunTurret,
	enInitDeleteTurretSprite_LaserTurret,
	enInitDeleteTurretSprite_RocketTurret,
};

class LeftWindow_Delete:public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void Init(InitDeleteTurretSprite initDeleteTurretSprite);

private:

	TurretManager*		m_turretManager;

	SpriteRender		m_spriteRender;

	Vector3				m_position;
	Vector3				m_deleteSpritePosition[12];

	bool				m_isDraw = false;

	int					m_initDeleteSpriteNumber = enInitDeleteTurretSprite_DualGunTurret;
};