#pragma once

class Energy;
class LeftWindow;
class LeftWindow_Delete;

class DualGunTurret;
class LaserTurret;
class RocketTurret;

class EnemyObject;

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

	/// <summary>
	/// タレットの削除確認用
	/// </summary>
	enum DeleteState
	{
		enDeleteState_Null,
		enDeleteState_Cancel,
		enDeleteState_Delete
	};

	/// <summary>
	/// タレットの画像用
	/// </summary>
	enum SpritePosition
	{
		enSpritePosition_DuarGunTurret,
		enSpritePosition_LaserTurret,
		enSpritePosition_RocketTurret
	};

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ステートを管理
	/// </summary>
	void StateManager();

	/// <summary>
	/// タレットの削除
	/// </summary>
	void DeleteTurret();

	/// <summary>
	/// 各タレットの作成
	/// </summary>
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

	//タレットの配列
	std::vector<IGameObject*>		m_turrets;

	//クラス
	Energy*							m_energy;
	LeftWindow*						m_leftWindow;
	LeftWindow_Delete*				m_leftWindowDelete[12];
	//タレット
	DualGunTurret*					m_dualGunTurret;
	LaserTurret*					m_laserTurret;
	RocketTurret*					m_rocketTurret;

	//モデル
	ModelRender						m_gridCursor;

	//Delete画像
	SpriteRender					m_deleteWindow;
	SpriteRender					m_deleteDelete;
	SpriteRender					m_deleteDeleteChoice;
	SpriteRender					m_deleteCancel;
	SpriteRender					m_deleteCancelChoice;
	float							m_deleteSpriteScale = 0.0f;

	//サウンド
	SoundSource*					m_setTurretSE;

	//カーソルポジション
	Vector3							m_cursorPosition;
	Vector3							m_deleteSpritePosition[12];

	//モデルの作成
	bool							m_isModelNewGO = false;
	bool							m_isGorstModelNewGO = false;
	
	//タレットの種類
	int								m_turretType = 0;

	//タレットの合計
	int								m_turretsSum = 0;

	//タレットの削除確認用ステート
	int								m_turretDeleteState = enDeleteState_Null;

	//タレットの回転
	float							m_rotation = 0.0f;
};