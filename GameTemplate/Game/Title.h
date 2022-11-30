#pragma once

class Game;

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

	//クラス
	Game*					m_game;

	//画像
	SpriteRender			m_titleSR;
};