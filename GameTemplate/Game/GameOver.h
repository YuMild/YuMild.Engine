#pragma once

class Game;

enum enGameOverState
{
	enGameOverState_BackGround,
	enGameOverState_GameOver,
	enGameOverState_PressAButton
};

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
class GameOver : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// HP�����炷
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
	/// HP���擾
	/// </summary>
	/// <returns></returns>
	const int& GetHP()
	{
		return m_hp;
	}

	/// <summary>
	/// �X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	const int& GetState()
	{
		return m_state;
	}

private:

	/// <summary>
	/// �X�R�A���Ǘ�
	/// </summary>
	void Score();

	/// <summary>
	/// �摜���Ǘ�
	/// </summary>
	void Sprite();

	//�N���X
	Game*				m_game				= nullptr;

	//�摜
	SpriteRender		m_backGroundSR;
	float				m_backGroundAlpha	= 0.0f;
	SpriteRender		m_windowSR;
	SpriteRender		m_pressAButtonSR;

	//�t�H���g
	FontRender			m_scoreFR;

	//HP
	int					m_hp				= 0;

	//�X�e�[�g
	int					m_state				= 0;
	float				m_stateTimer		= 0.0f;

	//�X�R�A
	float				m_score				= 0.0f;
};