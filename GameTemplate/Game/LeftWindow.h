#pragma once

class Player;
class TurretManager;

enum OperationState
{
	enOperationState_Normal_LeftWindow,
	enOperationState_SelectTurret_LeftWindow,
	enOperationState_SetTurret_LeftWindow,
	enOperationState_Delete_LeftWindow
};

class LeftWindow : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// 操作ステートを設定
	/// </summary>
	/// <param name="number"></param>
	void SetOperationState(OperationState operationState)
	{
		m_operationState = operationState;
	}

	/// <summary>
	/// 操作ステートを取得
	/// </summary>
	/// <returns></returns>
	int GetOperationState()
	{
		return m_operationState;
	}

	/// <summary>
	/// カーソルを一段上に
	/// </summary>
	void TurretCursorUp()
	{
		if (m_selectTurretNumber >= 4)
		{
			m_selectTurretNumber -= 4;
		}
		SoundPlayChoice();
	}

	/// <summary>
	/// カーソルを一段下に
	/// </summary>
	void TurretCursorDown()
	{
		if (m_selectTurretNumber <= 7)
		{
			m_selectTurretNumber += 4;
		}
		SoundPlayChoice();
	}

	/// <summary>
	/// カーソルを一段右に
	/// </summary>
	void TurretCursorRight()
	{
		if (m_selectTurretNumber != 3 && m_selectTurretNumber != 7 && m_selectTurretNumber != 11)
		{
			m_selectTurretNumber += 1;
		}
		SoundPlayChoice();
	}

	/// <summary>
	/// カーソルを一段左に
	/// </summary>
	void TurretCursorLeft()
	{
		if (m_selectTurretNumber != 0 && m_selectTurretNumber != 4 && m_selectTurretNumber != 8)
		{
			m_selectTurretNumber -= 1;
		}
		SoundPlayChoice();
	}

	/// <summary>
	/// 選択されているタレットを取得
	/// </summary>
	/// <returns></returns>
	int GetSelectTurretNumber()
	{
		return m_selectTurretNumber;
	}

private:

	/// <summary>
	/// 通常時
	/// </summary>
	void OperationNormal();

	/// <summary>
	/// タレット選択時
	/// </summary>
	void OperationSelectTurret();

	/// <summary>
	/// タレット作成時
	/// </summary>
	void OperationSetTurret();

	/// <summary>
	/// タレット削除時
	/// </summary>
	void OperationDelete();
	
	/// <summary>
	/// タレットを作成
	/// </summary>
	void MakeTurret();

	/// <summary>
	/// パラメーターバーを管理
	/// </summary>
	void SetParameterBar();

	/// <summary>
	/// ウィンドウ切り替え時の音声を再生
	/// </summary>
	void SoundPlayWindow()
	{
		m_windowSE = NewGO<SoundSource>(1);
		m_windowSE->Init(1);
		m_windowSE->SetVolume(1.0f);
		m_windowSE->Play(false);
	}

	/// <summary>
	/// 選択項目切り替え時の音声を再生
	/// </summary>
	void SoundPlayChoice()
	{
		m_choiceSE = NewGO<SoundSource>(2);
		m_choiceSE->Init(2);
		m_choiceSE->SetVolume(0.1f);
		m_choiceSE->Play(false);
	}

	Player*				m_player;
	TurretManager*		m_turretManager;

	SoundSource*		m_windowSE;
	SoundSource*		m_choiceSE;

	ModelRender			m_gridMR;

	SpriteRender		m_frameSR;
	SpriteRender		m_parameter_RangeSR;
	SpriteRender		m_parameter_DamageSR;
	SpriteRender		m_parameter_FireRateSR;
	SpriteRender		m_dualGunTurret_DetailSR;
	SpriteRender		m_laserTurret_DetailSR;
	SpriteRender		m_rocketTurret_DetailSR;
	SpriteRender		m_weapons_BackGroundSR;
	SpriteRender		m_delete_BackGroundSR;
	SpriteRender		m_turret_BackGroundSR;

	Vector3				m_turretBackGroundPosition[12];

	int					m_operationState = enOperationState_Normal_LeftWindow;
	int					m_selectTurretNumber = 0;

	float				m_rangeNumber = 0.0f;
	float				m_damageNumber = 0.0f;
	float				m_fireRateNumber = 0.0f;
	float				m_rangeSetNumber = 0.0f;
	float				m_damageSetNumber = 0.0f;
	float				m_fireRateSetNumber = 0.0f;
	float				m_move_Number = 0.0f;
};