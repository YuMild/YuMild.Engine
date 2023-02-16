#pragma once

class Container;
class GameCamera;
class GameOver;
class Stage;

enum enFadeState
{
	enFadeState_FadeIn,
	enFadeState_FadeOut
};

enum enEffectNumber
{
	enEffectNumber_Energy,
	enEffectNumber_Explosion,
	enEffectNumber_CursorAfter,
	enEffectNumber_Smoke,
	enEffectNumber_NormalTurret,
	enEffectNumber_DualGunTurret,
	enEffectNumber_LaserTurret,
	enEffectNumber_TeslaTurret,
	enEffectNumber_HolyTurret
};

enum enSoundNumber
{
	enSoundNumber_NormalBGM,
	enSoundNumber_Alarm,
	enSoundNumber_BossBGM,
	enSoundNumber_Window,
	enSoundNumber_Choice,
	enSoundNumber_CursorAfter,
	enSoundNumber_Explosion,
	enSoundNumber_NotEnoughCost,
	enSoundNumber_SetTurret,
	enSoundNumber_NormalTurret,
	enSoundNumber_DualGunTurret,
	enSoundNumber_LaserTurret,
	enSoundNumber_TeslaTurret,
	enSoundNumber_HolyTurret
};

/// <summary>
/// タイトル
/// </summary>
class Title : public IGameObject
{
public:

	Title();
	~Title();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

private:

	/// <summary>
	/// エフェクトを登録
	/// </summary>
	void InitEffect();

	/// <summary>
	/// サウンドを登録
	/// </summary>
	void InitSound();

	/// <summary>
	/// 動作を管理
	/// </summary>
	void Move();

	//クラス
	Container* m_container = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameOver* m_gameOver = nullptr;
	Stage* m_stage = nullptr;

	//画像
	SpriteRender			m_titleSR;
	SpriteRender			m_pressAButtonSR;

	bool					m_fadeState = 0;
	float					m_fadeTimer = 0.0f;
	float					m_fadeDelayTimer = 0.0f;
};