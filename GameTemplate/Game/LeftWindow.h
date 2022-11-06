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
	}

	/// <summary>
	/// 選択されているタレットを取得
	/// </summary>
	/// <returns></returns>
	int GetSelectTurretNumber()
	{
		return m_selectTurretNumber;
	}

	/// <summary>
	/// 削除したタレットの数を渡す
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	int SetDeleteTurretNumber(const int number)
	{
		m_deleteTurretNumber = number;

		//for(int i=number;number<=)
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
	/// ウィンドウ切り替え時の音声を再生
	/// </summary>
	void SoundPlayWindow()
	{
		m_choiceSE = NewGO<SoundSource>(1);
		m_choiceSE->Init(1);
		m_choiceSE->Play(false);
	}

	Player*				m_player;
	TurretManager*		m_turretManager;

	SoundSource*		m_choiceSE;

	ModelRender			m_gridMR;

	SpriteRender		m_frameSR;
	SpriteRender		m_dualGunTurret_DetailSR;
	SpriteRender		m_laserTurret_DetailSR;
	SpriteRender		m_rocketTurret_DetailSR;
	SpriteRender		m_deleteTurret[200];
	SpriteRender		m_weapons_BackGroundSR;
	SpriteRender		m_delete_BackGroundSR;
	SpriteRender		m_turret_BackGroundSR;

	Vector3				m_turretBackGroundPosition[12];
	Vector3				m_turretDeletePosition[12];

	int					m_operationState = enOperationState_Normal_LeftWindow;
	int					m_selectTurretNumber = 0;
	int					m_deleteTurretNumber = 0;
	int					m_turretSum = 0;

	float				m_move_Number = 0.0f;
};