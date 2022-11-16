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

	//�摜
	SpriteRender		m_windowSR;

	//HP
	int					m_hp = 0;
};