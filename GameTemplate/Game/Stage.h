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

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	//���f��
	Texture				m_stageEmissionMap;
	ModelRender			m_stageMR;
	Texture				m_campEmissionMap;
	ModelRender			m_campMR;

	//�w�i���f��
	ModelRender			m_earthMR;
	Quaternion			m_earthRotation				= Quaternion::Identity;
	ModelRender			m_moonMR;
	Quaternion			m_moonRotation				= Quaternion::Identity;
	Texture				m_spaceJunkEmissionMap;
	ModelRender			m_spaceJunkMR;
	Quaternion			m_spaceJunkRotation			= Quaternion::Identity;

	//����
	SoundSource*		m_normalBGM;
	SoundSource*		m_bossBGM;

	float				m_normalBGMVolume			= 0.0f;
};