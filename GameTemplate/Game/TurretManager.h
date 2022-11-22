#pragma once

class Energy;
class LeftWindow;
class LeftWindow_Delete;

class DualGunTurret;
class LaserTurret;
class RocketTurret;

class EnemyObject;

enum TurretType
{
	enTurret_DualGunTurret,
	enTurret_LaserTurret,
	enTurret_RocketTurret,
	en3,
	en4,
	en5,
	en6,
	en7,
	en8,
	en9,
	en10,
	en11
};

class TurretManager : public IGameObject
{
public:

	/// <summary>
	/// �^���b�g���쐬
	/// </summary>
	/// <param name="enturret"></param>
	void Init(TurretType enturret);

	/// <summary>
	/// �^���b�g�̍��v�����擾
	/// </summary>
	/// <returns></returns>
	int GetTurretSum() const
	{
		return m_turretsSum;
	}

private:

	/// <summary>
	/// �^���b�g�̍폜�m�F�p
	/// </summary>
	enum DeleteState
	{
		enDeleteState_Null,
		enDeleteState_Cancel,
		enDeleteState_Delete
	};

	/// <summary>
	/// �^���b�g�̉摜�p
	/// </summary>
	enum SpritePosition
	{
		enSpritePosition_DuarGunTurret,
		enSpritePosition_LaserTurret,
		enSpritePosition_RocketTurret
	};

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// �X�e�[�g���Ǘ�
	/// </summary>
	void StateManager();

	/// <summary>
	/// �^���b�g�̍폜
	/// </summary>
	void DeleteTurret();

	/// <summary>
	/// �e�^���b�g�̍쐬
	/// </summary>
	void MakeDualGunTurret();
	void MakeLaserTurret();
	void MakeRocketTurret();

	/// <summary>
	/// �^���b�g�Z�b�g���̉������Đ�
	/// </summary>
	void SoundPlaySetTurret()
	{
		m_setTurretSE = NewGO<SoundSource>(3);
		m_setTurretSE->Init(3);
		m_setTurretSE->SetVolume(0.15f);
		m_setTurretSE->Play(false);
	}

	//�^���b�g�̔z��
	std::vector<IGameObject*>		m_turrets;

	//�N���X
	Energy*							m_energy;
	LeftWindow*						m_leftWindow;
	LeftWindow_Delete*				m_leftWindowDelete[12];
	//�^���b�g
	DualGunTurret*					m_dualGunTurret;
	LaserTurret*					m_laserTurret;
	RocketTurret*					m_rocketTurret;

	//���f��
	ModelRender						m_gridCursor;

	//Delete�摜
	SpriteRender					m_deleteWindow;
	SpriteRender					m_deleteDelete;
	SpriteRender					m_deleteDeleteChoice;
	SpriteRender					m_deleteCancel;
	SpriteRender					m_deleteCancelChoice;
	float							m_deleteSpriteScale = 0.0f;

	//�T�E���h
	SoundSource*					m_setTurretSE;

	//�J�[�\���|�W�V����
	Vector3							m_cursorPosition;
	Vector3							m_deleteSpritePosition[12];

	//���f���̍쐬
	bool							m_isModelNewGO = false;
	bool							m_isGorstModelNewGO = false;
	
	//�^���b�g�̎��
	int								m_turretType = 0;

	//�^���b�g�̍��v
	int								m_turretsSum = 0;

	//�^���b�g�̍폜�m�F�p�X�e�[�g
	int								m_turretDeleteState = enDeleteState_Null;

	//�^���b�g�̉�]
	float							m_rotation = 0.0f;
};