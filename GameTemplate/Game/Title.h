#pragma once

class Game;

/// <summary>
/// �^�C�g��
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

	//�N���X
	Game*					m_game;

	//�摜
	SpriteRender			m_titleSR;
};