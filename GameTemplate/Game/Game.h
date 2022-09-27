#pragma once

class Game : public IGameObject
{
public:
	bool Start();
	void Render(RenderContext& renderContext);
	void Update();

private:
	ModelRender m_modelRender;
	float m_num;
	Vector3 m_pointLightPosition;
};