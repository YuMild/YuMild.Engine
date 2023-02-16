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

	InitEffect();
	InitSound();

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
		m_container		= NewGO<Container>(0, "container");
		m_gameCamera	= NewGO<GameCamera>(0, "gameCamera");
		m_gameOver		= NewGO<GameOver>(0, "gameOver");
		m_stage			= NewGO<Stage>(0, "stage");
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

void Title::InitEffect()
{
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_Energy, u"Assets/effect/Energy.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_Explosion, u"Assets/effect/Explosion.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_CursorAfter, u"Assets/effect/CursorAfter.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_Smoke, u"Assets/effect/Smoke.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_NormalTurret, u"Assets/effect/NormalTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_DualGunTurret, u"Assets/effect/DualGunTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_LaserTurret, u"Assets/Effect/LaserTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_TeslaTurret, u"Assets/effect/TeslaTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_HolyTurret, u"Assets/effect/HolyTurret.efk");
}

void Title::InitSound()
{
	g_soundEngine->ResistWaveFileBank(enSoundNumber_NormalBGM, "Assets/sound/NormalBGM.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Alarm, "Assets/sound/Alarm.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_BossBGM, "Assets/sound/BossBGM.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Window, "Assets/sound/Window.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Choice, "Assets/sound/Choice.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_CursorAfter, "Assets/sound/CursorAfter.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Explosion, "Assets/sound/Explosion.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_NormalTurret, "Assets/sound/NormalTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_DualGunTurret, "Assets/sound/DualGunTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_LaserTurret, "Assets/sound/LaserTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_TeslaTurret, "Assets/sound/TeslaTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_HolyTurret, "Assets/sound/HolyTurret.wav");
}