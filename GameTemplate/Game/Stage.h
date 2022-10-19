#pragma once
class Stage : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

private:

	ModelRender m_modelRender;
};