#include "stdafx.h"
#include "GameOver.h"

bool GameOver::Start()
{
	m_windowSR.Init("Assets/Sprite/GameOver/GameOver.dds", 1600.0f, 900.0f);
	m_windowSR.Update();

	m_hp = 3;

	//フォント
	m_scoreFR.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_scoreFR.SetScale(1.0f);
	m_scoreFR.SetPivot(1.0f, 0.5f);
	m_scoreFR.SetPosition({ 500.0f,400.0f,0.0f });

	return true;
}


void GameOver::Score()
{
	m_score += g_gameTime->GetFrameDeltaTime() * 100.0f;

	wchar_t score[256];
	swprintf_s(score, 256, L"%04d", int(m_score));
	m_scoreFR.SetText(score);
}

void GameOver::Update()
{
	Score();
}

void GameOver::Render(RenderContext& renderContext)
{
	//スコア
	m_scoreFR.Draw(renderContext);

	if (m_hp <= 0)
	{
		m_windowSR.Draw(renderContext);
	}
}