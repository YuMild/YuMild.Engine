#pragma once

class Player : public IGameObject
{
public:

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

};