#pragma once
class LeftWindow : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

private:

	SpriteRender		m_frame;
	SpriteRender		m_turretBackGround;
};