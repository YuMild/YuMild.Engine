#include "stdafx.h"
#include "GameOver.h"

#include "Game.h"

namespace
{
	const int DEFAULT_HP = 3;
}

bool GameOver::Start()
{
	//FindGO
	m_game = FindGO<Game>("game");
	
	//�摜
	m_backGroundSR.Init("Assets/Sprite/GameOver/BackGround.DDS", 1600.0f, 900.0f);
	m_backGroundSR.SetMulColor({ 1.0f,1.0f,1.0f,m_backGroundAlpha });
	m_backGroundSR.Update();
	m_windowSR.Init("Assets/Sprite/GameOver/GameOver.dds", 1600.0f, 900.0f);
	m_windowSR.Update();
	m_pressAButtonSR.Init("Assets/Sprite/GameOver/PressAButton.dds", 1600.0f, 900.0f);
	m_pressAButtonSR.Update();

	//�����l
	m_backGroundAlpha = 0.1f;

	//HP��ݒ�
	m_hp = DEFAULT_HP;

	//�t�H���g
	m_scoreFR.SetColor({ 0.3f,0.9f,1.0f,1.0f });
	m_scoreFR.SetScale(1.0f);
	m_scoreFR.SetPivot(1.0f, 0.5f);
	m_scoreFR.SetPosition({ 500.0f,400.0f,0.0f });

	return true;
}

void GameOver::Score()
{
	//�X�R�A
	if (m_hp > 0)
	{
		m_score += g_gameTime->GetFrameDeltaTime() * 100.0f;
	}
	
	wchar_t score[256];
	swprintf_s(score, 256, L"%04d", int(m_score));
	m_scoreFR.SetText(score);
}

void GameOver::Sprite()
{
	//�t�F�[�h�C��
	if (m_backGroundAlpha <= 0.7f)
	{
		m_backGroundAlpha *= 1.01f;
	}

	//�X�V����
	m_backGroundSR.SetMulColor({ 1.0f, 1.0f, 1.0f, m_backGroundAlpha });

	//�X�e�[�g�ύX
	m_stateTimer += g_gameTime->GetFrameDeltaTime();
	
	//3�b�o������X�e�[�g�ύX
	if (m_stateTimer >= 2.0f && m_backGroundAlpha >= 0.7f)
	{
		m_state += 1;
		m_stateTimer = 0.0f;
	}

	//�Q�[���X�e�[�g��ύX
	m_game->SetGameState(enGameState_Result);
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
	//�w�i
	if (m_state >= enGameOverState_BackGround)
	{
		m_backGroundSR.Draw(renderContext);
	}

	//�E�B���h�E
	if (m_state >= enGameOverState_GameOver)
	{
		m_windowSR.Draw(renderContext);
		m_scoreFR.Draw(renderContext);
	}

	//PressAButton>>Result
	if (m_state >= enGameOverState_PressAButton)
	{
		m_pressAButtonSR.Draw(renderContext);
	}
}