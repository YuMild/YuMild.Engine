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
	
	/// <summary>
	/// 削除用の画像を作成
	/// </summary>
	/// <param name="initDeleteTurretSprite"></param>
	void Init(InitDeleteTurretSprite initDeleteTurretSprite);

	/// <summary>
	/// 削除用の画像のポジションを設定
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

private:

	TurretManager*		m_turretManager;

	SpriteRender		m_spriteRender;

	Vector3				m_position;

	bool				m_isDraw = false;

	int					m_initDeleteSpriteNumber = enInitDeleteTurretSprite_DualGunTurret;
};