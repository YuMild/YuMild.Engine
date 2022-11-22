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

	/// <summary>
	/// スコアを管理
	/// </summary>
	void Score();

	//画像
	SpriteRender		m_windowSR;

	//フォント
	FontRender			m_scoreFR;

	//HP
	int					m_hp = 0;

	//スコア
	float				m_score = 0.0f;
};