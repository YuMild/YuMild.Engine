#pragma once

class Game;

enum enGameOverState
{
	enGameOverState_BackGround,
	enGameOverState_GameOver,
	enGameOverState_PressAButton
};

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
	const void SubHP()
	{
		m_hp -= 1;
		if (m_hp < 0)
		{
			m_hp = 0;
		}
	}

	/// <summary>
	/// HPを取得
	/// </summary>
	/// <returns></returns>
	const int& GetHP()
	{
		return m_hp;
	}

	/// <summary>
	/// ステートを取得
	/// </summary>
	/// <returns></returns>
	const int& GetState()
	{
		return m_state;
	}

private:

	/// <summary>
	/// スコアを管理
	/// </summary>
	void Score();

	/// <summary>
	/// 画像を管理
	/// </summary>
	void Sprite();

	//クラス
	Game*				m_game				= nullptr;

	//画像
	SpriteRender		m_backGroundSR;
	float				m_backGroundAlpha	= 0.0f;
	SpriteRender		m_windowSR;
	SpriteRender		m_pressAButtonSR;

	//フォント
	FontRender			m_scoreFR;

	//HP
	int					m_hp				= 0;

	//ステート
	int					m_state				= 0;
	float				m_stateTimer		= 0.0f;

	//スコア
	float				m_score				= 0.0f;
};