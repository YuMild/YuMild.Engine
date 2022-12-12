#pragma once

class Game;

/// <summary>
/// �Q�[���I�[�o�[
/// </summary>
class GameOver : public IGameObject
{
public:

	/// <summary>
	/// HP�����炷
	/// </summary>
	void SubHP()
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
	int GetHP()
	{
		return m_hp;
	}

	/// <summary>
	/// �X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	int GetState()
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

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	//�N���X
	Game*				m_game;

	//�摜
	SpriteRender		m_windowSR;
	SpriteRender		m_pressAButtonSR;

	//�t�H���g
	FontRender			m_scoreFR;

	//HP
	int					m_hp = 0;

	//�X�e�[�g
	int					m_state = 0;
	float				m_stateTimer = 0.0f;

	//�X�R�A
	float				m_score = 0.0f;
};