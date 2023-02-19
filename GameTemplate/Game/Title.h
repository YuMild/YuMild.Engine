#pragma once

class Game;

enum enFadeState
{
	enFadeState_FadeIn,
	enFadeState_FadeOut
};

/// <summary>
/// タイトル
/// </summary>
class Title : public IGameObject
{
public:

	Title();
	~Title();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

private:

	/// <summary>
	/// 動作を管理
	/// </summary>
	void Move();

	//クラス
	Game*					m_game				= nullptr;

	//画像
	SpriteRender			m_titleSR;
	SpriteRender			m_pressAButtonSR;

	bool					m_fadeState			= false;
	float					m_fadeTimer			= 0.0f;
	float					m_fadeDelayTimer	= 0.0f;
};