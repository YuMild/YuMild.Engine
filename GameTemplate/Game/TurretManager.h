#pragma once

class Energy;
class Game;
class LeftWindow;
class LeftWindowDelete;

class NormalTurret;
class DualGunTurret;
class LaserTurret;
class RocketTurret;
class GeneratorTurret;
class HealTurret;
class TeslaTurret;
class HolyTurret;

class EnemyObject;

enum TurretType
{
	enTurret_NormalTurret,
	enTurret_DualGunTurret,
	enTurret_LaserTurret,
	enTurret_RocketTurret,
	enTurret_GeneratorTurret,
	enTurret_HealTurret,
	enTurret_TeslaTurret,
	enTurret_HolyTurret,
	en7,
	en8,
	en9,
	en10,
};

/// <summary>
/// タレットを管理するクラス
/// </summary>
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

	bool Start() override;
	void Update() override;
	void Render(RenderContext& renderContext) override;

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
	void MakeNormalTurret();
	void MakeDualGunTurret();
	void MakeLaserTurret();
	void MakeRocketTurret();
	void MakeGeneratorTurret();
	void MakeHealTurret();
	void MakeTeslaTurret();
	void MakeHolyTurret();

	/// <summary>
	///	カーソル移動時のエフェクトを再生
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayCursorAfter(const Vector3& position);

	/// <summary>
	/// カーソル移動時の音声を再生
	/// </summary>
	void SoundPlayCursorAfter();

	/// <summary>
	/// タレットセット時の音声を再生
	/// </summary>
	void SoundPlaySetTurret();

	//タレットの配列
	std::vector<IGameObject*>		m_turrets;

	//クラス
	Energy*							m_energy;
	LeftWindow*						m_leftWindow;
	LeftWindowDelete*				m_leftWindowDelete[12];

	//タレット
	NormalTurret*					m_normalTurret;
	DualGunTurret*					m_dualGunTurret;
	LaserTurret*					m_laserTurret;
	RocketTurret*					m_rocketTurret;
	GeneratorTurret*				m_generatorTurret;
	HealTurret*						m_healTurret;
	TeslaTurret*					m_teslaTurret;
	HolyTurret*						m_holyTurret;

	//Delete画像
	SpriteRender					m_deleteWindow;
	SpriteRender					m_deleteDelete;
	SpriteRender					m_deleteDeleteChoice;
	SpriteRender					m_deleteCancel;
	SpriteRender					m_deleteCancelChoice;
	float							m_deleteSpriteScale = 0.0f;

	//エフェクト
	EffectEmitter*					m_cursorAfterEF;

	//サウンド
	SoundSource*					m_cursorAfterSE;
	SoundSource*					m_setTurretSE;

	//カーソルポジション
	Vector3							m_cursorPosition;
	Vector3							m_cursorPositionOld;
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