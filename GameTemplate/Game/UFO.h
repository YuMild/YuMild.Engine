#pragma once
class UFO : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

private:

	Vector3 m_position;
};