#pragma once
class GameOver : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// HP�����炷
	/// </summary>
	void SubHP()
	{
		m_hp -= 1;
	}

private:

	SpriteRender		m_windowSR;

	int					m_hp = 0;
};