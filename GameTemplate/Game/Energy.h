#pragma once

/// <summary>
/// エネルギー
/// </summary>
class Energy : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

private:

	/// <summary>
	/// 動作の管理
	/// </summary>
	void Move();

	/// <summary>
	/// 画像の管理
	/// </summary>
	void Sprite();

	//画像
	SpriteRender	m_windowSR;
	SpriteRender	m_circleSR;
	SpriteRender	m_gaugeSR;

	//エネルギー
	float			m_energy = 0.0f;

	//回転
	float			m_rotationNumber = 0.0f;
	Quaternion		m_rotation;
};