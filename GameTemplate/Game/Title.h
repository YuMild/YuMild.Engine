#pragma once

class Game;

enum enFadeState
{
	enFadeState_FadeIn,
	enFadeState_FadeOut
};

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

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	//�N���X
	Game*					m_game				= nullptr;

	//�摜
	SpriteRender			m_titleSR;
	SpriteRender			m_pressAButtonSR;

	bool					m_fadeState			= false;
	float					m_fadeTimer			= 0.0f;
	float					m_fadeDelayTimer	= 0.0f;
};