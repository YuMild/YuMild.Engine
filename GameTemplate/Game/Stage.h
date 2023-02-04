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

	//モデル
	Texture				m_stageEmissionMap;
	ModelRender			m_stageMR;
	Texture				m_campEmissionMap;
	ModelRender			m_campMR;

	//背景モデル
	ModelRender			m_earthMR;
	Quaternion			m_earthRotation				= Quaternion::Identity;
	ModelRender			m_moonMR;
	Quaternion			m_moonRotation				= Quaternion::Identity;
	Texture				m_spaceJunkEmissionMap;
	ModelRender			m_spaceJunkMR;
	Quaternion			m_spaceJunkRotation			= Quaternion::Identity;

	//音声
	SoundSource*		m_normalBGM;
	SoundSource*		m_bossBGM;

	float				m_normalBGMVolume			= 0.0f;
};