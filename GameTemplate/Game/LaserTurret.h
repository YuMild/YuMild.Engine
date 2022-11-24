#pragma once

class LeftWindow;

class LaserTurret : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// モデルのポジションを設定
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	void SetModelPosition(const Vector3& position)
	{
		m_modelPosition = position;
	}

	/// <summary>
	/// モデルのポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetModelPosition() const
	{
		return m_modelPosition;
	}

	/// <summary>
	/// 画像のポジションを設定
	/// </summary>
	/// <param name="position"></param>
	void SetSpritePosition(const Vector3& position)
	{
		m_spritePosition = position;
	}

	/// <summary>
	/// 画像のポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetSpritePosition() const
	{
		return m_spritePosition;
	}

private:

	//クラス
	LeftWindow*		m_leftWindow;

	//モデル
	ModelRender		m_modelRender;

	//画像
	SpriteRender	m_spriteRender;

	//モデル
	Vector3			m_modelPosition;
	Quaternion		m_modelRotation;
	Vector3			m_spritePosition;
};