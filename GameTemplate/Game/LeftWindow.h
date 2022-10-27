#pragma once

class Player;

class LeftWindow : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// ウィンドウを非表示にしている時の動作を管理
	/// </summary>
	void NormalMode();

	/// <summary>
	/// ウィンドウを表示している状態の動作を管理
	/// </summary>
	void CursorMode();

	/// <summary>
	/// 操作ステートを設定
	/// </summary>
	/// <param name="number"></param>
	void SetOperationState(const int number)
	{
		m_operationState = number;
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

private:

	enum OparationState
	{
		enOparationStateNormal,
		enOparationStateSelectTurret,
	};

	Player*				m_player;

	SpriteRender		m_frame;
	SpriteRender		m_turretBackGround;

	Vector3				m_turretBackGroundPosition[12];

	int					m_operationState = enOparationStateNormal;
	int					m_selectTurretNumber = 0;

	float				m_move_Number = 0.0f;
};