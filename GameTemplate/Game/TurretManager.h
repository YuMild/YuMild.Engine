#pragma once

class Energy;
class Game;
class LeftWindow;
class LeftWindowDelete;

class NormalTurret;
class DualGunTurret;
class LaserTurret;
class RocketTurret;
class GeneratorTurret;
class HealTurret;
class TeslaTurret;
class HolyTurret;

class EnemyObject;

enum TurretType
{
	enTurret_NormalTurret,
	enTurret_DualGunTurret,
	enTurret_LaserTurret,
	enTurret_RocketTurret,
	enTurret_GeneratorTurret,
	enTurret_HealTurret,
	enTurret_TeslaTurret,
	enTurret_HolyTurret,
	en7,
	en8,
	en9,
	en10,
};

/// <summary>
/// �^���b�g���Ǘ�����N���X
/// </summary>
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
	const int& GetTurretSum() const
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

	bool Start() override;
	void Update() override;
	void Render(RenderContext& renderContext) override;

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
	void MakeNormalTurret();
	void MakeDualGunTurret();
	void MakeLaserTurret();
	void MakeRocketTurret();
	void MakeGeneratorTurret();
	void MakeHealTurret();
	void MakeTeslaTurret();
	void MakeHolyTurret();

	/// <summary>
	///	�J�[�\���ړ����̃G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayCursorAfter(const Vector3& position);

	/// <summary>
	/// �J�[�\���ړ����̉������Đ�
	/// </summary>
	void SoundPlayCursorAfter();

	/// <summary>
	/// �^���b�g�Z�b�g���̉������Đ�
	/// </summary>
	void SoundPlaySetTurret();

	//�^���b�g�̔z��
	std::vector<IGameObject*>		m_turrets;

	//�N���X
	Energy*							m_energy					= nullptr;
	LeftWindow*						m_leftWindow				= nullptr;
	LeftWindowDelete*				m_leftWindowDelete[12];

	//�^���b�g
	NormalTurret*					m_normalTurret				= nullptr;
	DualGunTurret*					m_dualGunTurret				= nullptr;
	LaserTurret*					m_laserTurret				= nullptr;
	RocketTurret*					m_rocketTurret				= nullptr;
	GeneratorTurret*				m_generatorTurret			= nullptr;
	HealTurret*						m_healTurret				= nullptr;
	TeslaTurret*					m_teslaTurret				= nullptr;
	HolyTurret*						m_holyTurret				= nullptr;

	//Delete�摜
	SpriteRender					m_deleteWindow;
	SpriteRender					m_deleteDelete;
	SpriteRender					m_deleteDeleteChoice;
	SpriteRender					m_deleteCancel;
	SpriteRender					m_deleteCancelChoice;
	float							m_deleteSpriteScale			= 0.0f;

	//�G�t�F�N�g
	EffectEmitter*					m_cursorAfterEF				= nullptr;

	//�T�E���h
	SoundSource*					m_cursorAfterSE				= nullptr;
	SoundSource*					m_setTurretSE				= nullptr;

	//�J�[�\���|�W�V����
	Vector3							m_cursorPosition			= Vector3::Zero;
	Vector3							m_cursorPositionOld			= Vector3::Zero;
	Vector3							m_deleteSpritePosition[12];

	//���f���̍쐬
	bool							m_isModelNewGO				= false;
	bool							m_isGorstModelNewGO			= false;
	
	//�^���b�g�̎��
	int								m_turretType				= 0;

	//�^���b�g�̍��v
	int								m_turretsSum				= 0;

	//�^���b�g�̍폜�m�F�p�X�e�[�g
	int								m_turretDeleteState			= enDeleteState_Null;

	//�^���b�g�̉�]
	float							m_rotation					= 0.0f;
};