#include "stdafx.h"
#include "GameOver.h"

#include "Game.h"

namespace
{
	int DEFAULT_HP = 3;
}

bool GameOver::Start()
{
	//FindGO
	m_game = FindGO<Game>("game");

	//画像
	m_backGroundSR.Init("Assets/Sprite/GameOver/BackGround.DDS", 1600.0f, 900.0f);
	m_backGroundSR.SetMulColor({ 1.0f,1.0f,1.0f,m_backGroundAlpha });
	m_backGroundSR.Update();
	m_windowSR.Init("Assets/Sprite/GameOver/GameOver.dds", 1600.0f, 900.0f);
	m_windowSR.Update();
	m_pressAButtonSR.Init("Assets/Sprite/GameOver/PressAButton.dds", 1600.0f, 900.0f);
	m_pressAButtonSR.Update();

	//HPを設定
	m_hp = DEFAULT_HP;

	//フォント
	m_scoreFR.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_scoreFR.SetScale(1.0f);
	m_scoreFR.SetPivot(1.0f, 0.5f);
	m_scoreFR.SetPosition({ 500.0f,400.0f,0.0f });

	return true;
}

void GameOver::Score()
{
	//スコア
	m_score += g_gameTime->GetFrameDeltaTime() * 100.0f;

	wchar_t score[256];
	swprintf_s(score, 256, L"%04d", int(m_score));
	m_scoreFR.SetText(score);
}

void GameOver::Sprite()
{
	m_stateTimer += g_gameTime->GetFrameDeltaTime();

	//フェードイン
	if (m_backGroundAlpha <= 0.7f)
	{
		m_backGroundAlpha += g_gameTime->GetFrameDeltaTime() / 10.0f;
	}

	m_backGroundSR.SetMulColor({ 1.0f, 1.0f, 1.0f, m_backGroundAlpha });

	//3秒経ったらステート変更
	if (m_stateTimer >= 3.0f)
	{
		m_state += 1;
		m_stateTimer = 0.0f;
	}

	//ゲームステートを変更
	m_game->SetGameState(enGameState_GameOver);
}

void GameOver::Update()
{
	Score();
	if (m_hp <= 0)
	{
		Sprite();
	}
}

void GameOver::Render(RenderContext& renderContext)
{
	//背景
	if (m_state >= 0)
	{
		m_backGroundSR.Draw(renderContext);
	}

	//ウィンドウ
	if (m_state >= 1)
	{
		m_windowSR.Draw(renderContext);
		m_scoreFR.Draw(renderContext);
	}

	//PressAButton>>Result
	if (m_state >= 2)
	{
		m_pressAButtonSR.Draw(renderContext);
	}
}