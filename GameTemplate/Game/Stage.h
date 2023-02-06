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

	/// <summary>
	/// �G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayEnergy(const Vector3& position);

	//���f��
	Texture				m_stageEmissionMap;
	ModelRender			m_stageMR;
	Texture				m_campEmissionMap;
	ModelRender			m_campMR;
	EffectEmitter*		m_energyEF;

	//�w�i���f��
	Texture				m_earthEmissionMap;
	ModelRender			m_earthMR;
	Quaternion			m_earthRotation				= Quaternion::Identity;
	ModelRender			m_moonMR;
	Quaternion			m_moonRotation				= Quaternion::Identity;
	Texture				m_spaceJunkEmissionMap;
	ModelRender			m_spaceJunkMR;
	Quaternion			m_spaceJunkRotation			= Quaternion::Identity;
	//覐ΌQ
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

	//����
	SoundSource*		m_normalBGM;
	SoundSource*		m_bossBGM;

	float				m_normalBGMVolume			= 0.0f;
};