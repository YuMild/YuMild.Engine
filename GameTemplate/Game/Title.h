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
/// �^�C�g��
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
	/// �G�t�F�N�g��o�^
	/// </summary>
	void InitEffect();

	/// <summary>
	/// �T�E���h��o�^
	/// </summary>
	void InitSound();

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	//�N���X
	Container* m_container = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameOver* m_gameOver = nullptr;
	Stage* m_stage = nullptr;

	//�摜
	SpriteRender			m_titleSR;
	SpriteRender			m_pressAButtonSR;

	bool					m_fadeState = 0;
	float					m_fadeTimer = 0.0f;
	float					m_fadeDelayTimer = 0.0f;
};