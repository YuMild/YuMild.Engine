#pragma once

class LeftWindow;
class LeftWindow_Delete;

class DualGunTurret;
class LaserTurret;
class RocketTurret;

enum TurretType
{
	enTurret_DualGunTurret,
	enTurret_LaserTurret,
	enTurret_RocketTurret,
	en3,
	en4,
	en5,
	en6,
	en7,
	en8,
	en9,
	en10,
	en11
};

class TurretManager : public IGameObject
{
public:

	/// <summary>
	/// タレットを作成
	/// </summary>
	/// <param name="enturret"></param>
	void Init(TurretType enturret);

	/// <summary>
	/// タレットの合計数を取得
	/// </summary>
	/// <returns></returns>
	int GetTurretSum() const
	{
		return m_turretsSum;
	}

private:

	enum DeleteState
	{
		enDeleteState_Null,
		enDeleteState_Cancel,
		enDeleteState_Delete
	};

	enum SpritePosition
	{
		enSpritePosition_DuarGunTurret,
		enSpritePosition_LaserTurret,
		enSpritePosition_RocketTurret
	};

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void StateManager();
	void DeleteTurret();
	void MakeDualGunTurret();
	void MakeLaserTurret();
	void MakeRocketTurret();

	/// <summary>
	/// タレットセット時の音声を再生
	/// </summary>
	void SoundPlaySetTurret()
	{
		m_setTurretSE = NewGO<SoundSource>(3);
		m_setTurretSE->Init(3);
		m_setTurretSE->SetVolume(0.15f);
		m_setTurretSE->Play(false);
	}

	std::vector<IGameObject*>		m_turrets;

	//クラス
	LeftWindow*						m_leftWindow;
	LeftWindow_Delete*				m_leftWindow_Delete[12];
	
	DualGunTurret*					m_dualGunTurret;
	LaserTurret*					m_laserTurret;
	RocketTurret*					m_rocketTurret;

	//Delete
	SpriteRender					m_delete_Window;
	SpriteRender					m_delete_Delete;
	SpriteRender					m_delete_DeleteChoice;
	SpriteRender					m_delete_Cancel;
	SpriteRender					m_delete_CancelChoice;

	//サウンド
	SoundSource*					m_setTurretSE;

	Vector3							m_cursorPosition;
	Vector3							m_deleteSpritePosition[12];

	bool							m_isModelNewGO = false;
	bool							m_isGorstModelNewGO = false;
	
	int								m_turretType = 0;
	int								m_turretsSum = 0;
	int								m_turretDeleteState = enDeleteState_Null;

	float							m_rotation = 0.0f;
};