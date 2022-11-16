#pragma once

/// <summary>
/// ゲームオーバー
/// </summary>
class GameOver : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// HPを減らす
	/// </summary>
	void SubHP()
	{
		m_hp -= 1;
	}

private:

	//画像
	SpriteRender		m_windowSR;

	//HP
	int					m_hp = 0;
};