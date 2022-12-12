#pragma once

class LeftWindow;
class TurretManager;

enum InitDeleteTurretSprite
{
	enInitDeleteTurretSprite_NormalTurret,
	enInitDeleteTurretSprite_DualGunTurret,
	enInitDeleteTurretSprite_LaserTurret,
	enInitDeleteTurretSprite_RocketTurret,
	enInitDeleteTurretSprite_GenerationTurret,
	enInitDeleteTurretSprite_HealTurret,
	enInitDeleteTurretSprite_Null
};

class LeftWindowDelete : public IGameObject
{
public:
	
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
	void SetIsDraw(const bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/// <summary>
	/// ドローするか否か取得
	/// </summary>
	/// <returns></returns>
	bool GetIsDraw()const
	{
		return m_isDraw;
	}

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	//クラス
	LeftWindow*			m_leftWindow;
	TurretManager*		m_turretManager;

	//画像
	SpriteRender		m_spriteRender;

	//ポジション
	Vector3				m_position;

	//ドローするか否か
	bool				m_isDraw = false;

	//描画するタレットの種類
	int					m_initDeleteSpriteNumber = enInitDeleteTurretSprite_Null;
};