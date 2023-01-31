#pragma once

#include "Game.h"

class Game;

/// <summary>
/// �X�e�[�W���Ǘ�����N���X
/// </summary>
class Stage : public IGameObject
{
public:

	/// <summary>
	/// �ʏ펞��BGM�ɐ؂�ւ���
	/// </summary>
	void SetNormalBGM();

	/// <summary>
	/// BOSS���BGM�ɐ؂�ւ���
	/// </summary>
	void SetBossBGM();

	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

private:

	//���f��
	Texture				m_stageEmissionMap;
	ModelRender			m_stageMR;
	Texture				m_campEmissionMap;
	ModelRender			m_campMR;

	//����
	SoundSource*		m_normalBGM;
	SoundSource*		m_bossBGM;

	float				m_normalBGMVolume = 0.0f;
};