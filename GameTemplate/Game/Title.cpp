#include "stdafx.h"
#include "Title.h"

#include "Container.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Stage.h"

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
	//画像
	m_titleSR.Init("Assets/sprite/Title/Title.dds", 1600.0f, 900.0f);
	m_titleSR.SetScale({ 1.0f,1.0f,1.0f });
	m_titleSR.Update();
	m_pressAButtonSR.Init("Assets/sprite/Title/Title_PressAButton.dds", 1600.0f, 900.0f);
	m_pressAButtonSR.SetScale({ 1.0f,1.0f,1.0f });
	m_pressAButtonSR.Update();

	return true;
}

void Title::Move()
{
	//フェードイン中なら
	if (m_fadeState == enFadeState_FadeIn && m_fadeTimer <= 1.0f)
	{
		m_fadeTimer += g_gameTime->GetFrameDeltaTime();
	}
	//フェードアウト中なら
	else if (m_fadeState == enFadeState_FadeOut && m_fadeTimer >= 0.0f)
	{
		m_fadeTimer -= g_gameTime->GetFrameDeltaTime();
	}

	//フェードアウト
	if (m_fadeTimer <= 0.0f)
	{
		m_fadeState = enFadeState_FadeIn;
	}
	//フェードアウト
	else if (m_fadeTimer >= 1.0f)
	{
		m_fadeDelayTimer += g_gameTime->GetFrameDeltaTime();
		if (m_fadeDelayTimer >= 0.5f)
		{
			m_fadeDelayTimer = 0.0f;
			m_fadeState = enFadeState_FadeOut;
		}
	}

	//アルファ値を変更
	m_pressAButtonSR.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeTimer });
	m_pressAButtonSR.Update();

	//ボタンを押すとゲームスタート
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_game = NewGO<Game>(0, "game");
		m_game->SetGameState(enGameState_Container);
		DeleteGO(this);
	}
}

void Title::Update()
{
	Move();
}

void Title::Render(RenderContext& renderContext)
{
	m_titleSR.Draw(renderContext);
	m_pressAButtonSR.Draw(renderContext);
}