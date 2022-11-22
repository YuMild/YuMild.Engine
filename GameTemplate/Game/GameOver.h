#pragma once

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
	void SubHP()
	{
		m_hp -= 1;
	}

private:

	/// <summary>
	/// �X�R�A���Ǘ�
	/// </summary>
	void Score();

	//�摜
	SpriteRender		m_windowSR;

	//�t�H���g
	FontRender			m_scoreFR;

	//HP
	int					m_hp = 0;

	//�X�R�A
	float				m_score = 0.0f;
};