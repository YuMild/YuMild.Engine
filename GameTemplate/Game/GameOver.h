#pragma once

class Game;

/// <summary>
/// ゲームオーバー
/// </summary>
class GameOver : public IGameObject
{
public:

	/// <summary>
	/// HPを減らす
	/// </summary>
	void SubHP()
	{
		m_hp -= 1;
	}

	/// <summary>
	/// HPを取得
	/// </summary>
	/// <returns></returns>
	int GetHP()
	{
		return m_hp;
	}

	/// <summary>
	/// ステートを取得
	/// </summary>
	/// <returns></returns>
	int GetState()
	{
		return m_state;
	}

private:

	/// <summary>
	/// スコアを管理
	/// </summary>
	void Score();

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	//クラス
	Game*				m_game;

	//画像
	SpriteRender		m_windowSR;

	//フォント
	FontRender			m_scoreFR;

	//HP
	int					m_hp = 0;

	//ステート
	int					m_state = 0;

	//スコア
	float				m_score = 0.0f;
};