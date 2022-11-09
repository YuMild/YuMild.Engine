#pragma once

class LeftWindow;
class TurretManager;

enum InitDeleteTurretSprite
{
	enInitDeleteTurretSprite_DualGunTurret,
	enInitDeleteTurretSprite_LaserTurret,
	enInitDeleteTurretSprite_RocketTurret,
	enInitDeleteTurretSprite_Null
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
	/// 削除用の画像を作成
	/// </summary>
	/// <param name="number"></param>
	void Init(int number);

	/// <summary>
	/// タレットの種類を取得
	/// </summary>
	/// <returns></returns>
	int GetTurretType() const
	{
		return m_initDeleteSpriteNumber;
	}

	/// <summary>
	/// 削除用の画像のポジションを設定
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 削除用の画像のポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ドローするか否か設定
	/// </summary>
	/// <param name="isDraw"></param>
	void SetDraw(const bool isDraw)
	{
		m_isDraw = isDraw;
	}

private:

	LeftWindow*			m_leftWindow;
	TurretManager*		m_turretManager;

	SpriteRender		m_spriteRender;

	Vector3				m_position;

	bool				m_isDraw = false;

	int					m_initDeleteSpriteNumber = enInitDeleteTurretSprite_DualGunTurret;
};