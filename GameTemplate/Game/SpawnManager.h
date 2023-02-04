#pragma once

#include "UFO.h"
#include "Missile.h"
#include "Game.h"
#include "SpaceShip.h"

class Game;

/// <summary>
/// 敵のスポーンを管理するクラス
/// </summary>
class SpawnManager : public IGameObject
{
public:

	~SpawnManager();
	bool Start()override;
	void Update()override;
	void UpdateOnStop()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// UFOのデフォルトHPを設定
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_UFO()
	{
		return m_defaultHP_UFO;
	}

	/// <summary>
	/// MissileのデフォルトHPを設定
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_Missile()
	{
		return m_defaultHP_Missile;
	}

	/// <summary>
	/// SpaceShipのデフォルトHPを設定
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_SpaceShip()
	{
		return m_defaultHP_SpaceShip;
	}

	/// <summary>
	/// 爆破エフェクトを再生
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayExplosion(Vector3& position);

	/// <summary>
	/// 爆破音声を再生
	/// </summary>
	void SoundPlayExplosion();

private:

	/// <summary>
	/// レベルアップ
	/// </summary>
	void LevelUp();

	/// <summary>
	/// UFOのスポーンを管理
	/// </summary>
	void SpawnUFO();

	/// <summary>
	/// Missileのスポーンを管理
	/// </summary>
	void SpawnMissile();

	/// <summary>
	/// SpaceShipのスポーンを管理
	/// </summary>
	void SpawnSpaceShip();

	/// <summary>
	/// ボス出現時の音声を再生
	/// </summary>
	void SoundPlayBossSpawn();

	//クラス
	Missile*		m_missile;
	UFO*			m_ufo;
	SpaceShip*		m_spaceShip;

	//エフェクト
	EffectEmitter*	m_explosionEF;

	//音声
	SoundSource*	m_explosionSE;
	SoundSource*	m_bossSpawnSE;;

	//画像
	SpriteRender	m_warningSR;
	SpriteRender	m_warningRightCircleSR;
	SpriteRender	m_warningLeftCircleSR;

	//アップデートを止めているか否か
	bool			m_isStop = false;

	//Warningを管理する
	bool			m_fade = true;
	float			m_warningTimer = 0.0f;
	float			m_stopTimer = 0.0f;
	Quaternion		m_warningRightCircle_Rotation;
	Quaternion		m_warningLeftCircle_Rotation;
	float			m_warningRightCircle_RotationNumber = 0.0f;
	float			m_warningLeftCircle_RotationNumber = 0.0f;

	//レベルを管理するタイマー
	float			m_levelTimer = 0.0f;

	//UFO
	float			m_spawnTime_UFO = 0.0f;
	float			m_spawnTimer_UFO = 0.0f;
	float			m_defaultHP_UFO = 0.0f;

	//Missile
	float			m_spawnTime_Missile = 0.0f;
	float			m_spawnTimer_Missile = 0.0f;
	float			m_defaultHP_Missile = 0.0f;

	//SpaceShip
	float			m_spawnTime_SpaceShip = 0.0f;
	float			m_spawnTimer_SpaceShip = 0.0f;
	float			m_defaultHP_SpaceShip = 0.0f;
};