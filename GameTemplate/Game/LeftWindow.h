#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

class Energy;
class Game;
class GameCamera;
class LeftWindowDelete;
class Player;
class SpaceShip;
class TurretManager;

enum OperationState
{
	enOperationState_Normal_LeftWindow,
	enOperationState_SelectTurret_LeftWindow,
	enOperationState_SetTurret_LeftWindow,
	enOperationState_Delete_LeftWindow,
	enOperationState_DeleteCheck_LeftWindow
};

class LeftWindow : public IGameObject
{
public:

	/// <summary>
	/// 操作ステートを設定
	/// </summary>
	/// <param name="number"></param>
	const void SetOperationState(OperationState operationState)
	{
		m_operationState = operationState;
	}

	/// <summary>
	/// 操作ステートを取得
	/// </summary>
	/// <returns></returns>
	const int& GetOperationState()
	{
		return m_operationState;
	}

	/// <summary>
	/// 移動距離を取得
	/// </summary>
	/// <returns></returns>
	const float& GetMoveNumber()
	{
		return m_moveNumber;
	}

	/// <summary>
	/// カーソルを一段上に
	/// </summary>
	const void TurretCursorUp()
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
	const void TurretCursorDown()
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
	const void TurretCursorRight()
	{
		if (m_selectTurretNumber != 11)
		{
			m_selectTurretNumber += 1;
		}
		SoundPlayChoice();
	}

	/// <summary>
	/// カーソルを一段左に
	/// </summary>
	const void TurretCursorLeft()
	{
		if (m_selectTurretNumber != 0)
		{
			m_selectTurretNumber -= 1;
		}
		SoundPlayChoice();
	}

	/// <summary>
	/// 選択されているタレットを取得
	/// </summary>
	/// <returns></returns>
	const int& GetSelectTurretNumber()
	{
		return m_selectTurretNumber;
	}

	/// <summary>
	/// ボタンのディレイを有効化する
	/// </summary>
	const void SetButtonDelay()
	{
		m_buttonDelay = 0.0f;
	}

	/// <summary>
	/// ボタンが使用可能か否か取得
	/// </summary>
	/// <returns></returns>
	const bool& GetButtonReady()
	{
		return m_buttonReady;
	}

	/// <summary>
	/// ウィンドウ切り替え時の音声を再生
	/// </summary>
	void SoundPlayWindow();

	/// <summary>
	/// 選択項目切り替え時の音声を再生
	/// </summary>
	void SoundPlayChoice();

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

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
	/// タレット削除確認時
	/// </summary>
	void OperationDeleteCheck();

	/// <summary>
	/// パラメーターバーを管理
	/// </summary>
	void SetParameterBar();

	//クラス
	Energy*						m_energy						= nullptr;
	GameCamera*					m_gameCamera					= nullptr;
	LeftWindowDelete*			m_leftWindowDelete				= nullptr;
	Player*						m_player						= nullptr;
	SpaceShip*					m_spaceShip						= nullptr;
	TurretManager*				m_turretManager					= nullptr;
	std::vector<TurretObject*>	m_turrets;
	std::vector<EnemyObject*>	m_enemys;

	//音声
	SoundSource*				m_windowSE						= nullptr;
	SoundSource*				m_choiceSE						= nullptr;

	//モデル
	ModelRender					m_gridMR;
	ModelRender					m_gridCursorMR;
	Vector3						m_gridCursorPosition			= Vector3::Zero;

	//画像
	//枠
	SpriteRender				m_frameSR;
	//パラメーター
	SpriteRender				m_parameter_RangeSR;
	SpriteRender				m_parameter_DamageSR;
	SpriteRender				m_parameter_FireRateSR;
	//詳細
	SpriteRender				m_detail_NormalTurretSR;
	SpriteRender				m_detail_DualGunTurretSR;
	SpriteRender				m_detail_LaserTurretSR;
	SpriteRender				m_detail_RocketTurretSR;
	SpriteRender				m_detail_GenerationTurretSR;
	SpriteRender				m_detail_HealTurretSR;
	SpriteRender				m_detail_TeslaTurretSR;
	SpriteRender				m_detail_HolyTurretSR;
	//説明文
	SpriteRender				m_descride_NormalTurretSR;
	SpriteRender				m_descride_DualGunTurretSR;
	SpriteRender				m_descride_LaserTurretSR;
	SpriteRender				m_descride_RocketTurretSR;
	SpriteRender				m_descride_GenerationTurretSR;
	SpriteRender				m_descride_HealTurretSR;
	SpriteRender				m_descride_TeslaTurretSR;
	SpriteRender				m_descride_HolyTurretSR;
	//背景
	SpriteRender				m_weapons_BackGroundSR;
	SpriteRender				m_delete_BackGroundSR;
	SpriteRender				m_turret_BackGroundSR;
	//UIアニメーション
	SpriteRender				m_choiceEffectSR;

	//背景のポジション
	Vector3						m_turretBackGroundPosition[12];
	//UIアニメーションのポジション
	Vector3						m_choiceEffectPosition			= Vector3::Zero;

	//ステート
	int							m_operationState				= enOperationState_Normal_LeftWindow;

	//選択しているタレット
	int							m_selectTurretNumber			= 0;

	//ボタンの重複が起きないようディレイをかける
	bool						m_buttonReady					= false;
	float						m_buttonDelay					= 0.0f;

	//パラメーター
	float						m_rangeNumber					= 0.0f;
	float						m_damageNumber					= 0.0f;
	float						m_fireRateNumber				= 0.0f;
	float						m_rangeSetNumber				= 0.0f;
	float						m_damageSetNumber				= 0.0f;
	float						m_fireRateSetNumber				= 0.0f;

	//ウィンドウのポジションに加算する数値
	float						m_moveNumber					= 0.0f;
};