#pragma once

class Game : public IGameObject
{
public:
	bool Start();
	void Render(RenderContext& renderContext);
	void Update();

private:
	ModelRender m_modelRender;
	ModelRender m_modelRenderReciever;
	float m_num;
	Vector3 m_pointLightPosition;
};