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

	//モデル
	Texture				m_stageEmissionMap;
	ModelRender			m_stageMR;
	Texture				m_campEmissionMap;
	ModelRender			m_campMR;

	//音声
	SoundSource*		m_normalBGM;
	SoundSource*		m_bossBGM;

	float				m_normalBGMVolume = 0.0f;
};