#pragma once

class Player : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

private:
};