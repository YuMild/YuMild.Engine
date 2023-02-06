#pragma once

#include "Game.h"

class Game;

/// <summary>
/// ステージを管理するクラス
/// </summary>
class Stage : public IGameObject
{
public:

	/// <summary>
	/// 通常時のBGMに切り替える
	/// </summary>
	void SetNormalBGM();

	/// <summary>
	/// BOSS戦のBGMに切り替える
	/// </summary>
	void SetBossBGM();

	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

private:

	/// <summary>
	/// 動作を管理
	/// </summary>
	void Move();

	/// <summary>
	/// エフェクトを再生
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayEnergy(const Vector3& position);

	//モデル
	Texture				m_stageEmissionMap;
	ModelRender			m_stageMR;
	Texture				m_campEmissionMap;
	ModelRender			m_campMR;
	EffectEmitter*		m_energyEF;

	//背景モデル
	Texture				m_earthEmissionMap;
	ModelRender			m_earthMR;
	Quaternion			m_earthRotation				= Quaternion::Identity;
	ModelRender			m_moonMR;
	Quaternion			m_moonRotation				= Quaternion::Identity;
	Texture				m_spaceJunkEmissionMap;
	ModelRender			m_spaceJunkMR;
	Quaternion			m_spaceJunkRotation			= Quaternion::Identity;
	//隕石群
	ModelRender			m_asteroid1MR;
	Quaternion			m_asteroid1Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid2MR;
	Quaternion			m_asteroid2Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid3MR;
	Quaternion			m_asteroid3Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid4MR;
	Quaternion			m_asteroid4Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid5MR;
	Quaternion			m_asteroid5Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid6MR;
	Quaternion			m_asteroid6Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid7MR;
	Quaternion			m_asteroid7Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid8MR;
	Quaternion			m_asteroid8Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid9MR;
	Quaternion			m_asteroid9Rotation			= Quaternion::Identity;
	ModelRender			m_asteroid10MR;
	Quaternion			m_asteroid10Rotation		= Quaternion::Identity;

	//音声
	SoundSource*		m_normalBGM;
	SoundSource*		m_bossBGM;

	float				m_normalBGMVolume			= 0.0f;
};