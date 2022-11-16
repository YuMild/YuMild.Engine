#include "stdafx.h"
#include "GameOver.h"

bool GameOver::Start()
{
	m_windowSR.Init("Assets/Sprite/GameOver/GameOver.dds", 1600.0f, 900.0f);
	m_windowSR.Update();

	m_hp = 3;

	return true;
}

void GameOver::Update()
{

}

void GameOver::Render(RenderContext& renderContext)
{
	if (m_hp <= 0)
	{
		m_windowSR.Draw(renderContext);
	}
}