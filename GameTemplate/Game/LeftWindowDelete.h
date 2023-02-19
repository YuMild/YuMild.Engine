#pragma once

class LeftWindow;
class TurretManager;

enum InitDeleteTurretSprite
{
	enInitDeleteTurretSprite_NormalTurret,
	enInitDeleteTurretSprite_DualGunTurret,
	enInitDeleteTurretSprite_LaserTurret,
	enInitDeleteTurretSprite_RocketTurret,
	enInitDeleteTurretSprite_GenerationTurret,
	enInitDeleteTurretSprite_HealTurret,
	enInitDeleteTurretSprite_TeslaTurret,
	enInitDeleteTurretSprite_HolyTurret,
	enInitDeleteTurretSprite_Null
};

class LeftWindowDelete : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;
	
	/// <summary>
	/// �폜�p�̉摜���쐬
	/// </summary>
	/// <param name="initDeleteTurretSprite"></param>
	void Init(InitDeleteTurretSprite initDeleteTurretSprite);

	/// <summary>
	/// �폜�p�̉摜���쐬
	/// </summary>
	/// <param name="number"></param>
	void Init(int number);

	/// <summary>
	/// �^���b�g�̎�ނ��擾
	/// </summary>
	/// <returns></returns>
	const int& GetTurretType() const
	{
		return m_initDeleteSpriteNumber;
	}

	/// <summary>
	/// �폜�p�̉摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	const void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// �폜�p�̉摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �h���[���邩�ۂ��ݒ�
	/// </summary>
	/// <param name="isDraw"></param>
	const void SetIsDraw(const bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/// <summary>
	/// �h���[���邩�ۂ��擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsDraw()const
	{
		return m_isDraw;
	}

private:

	//�N���X
	LeftWindow*			m_leftWindow				= nullptr;
	TurretManager*		m_turretManager				= nullptr;

	//�摜
	SpriteRender		m_spriteRender;

	//�|�W�V����
	Vector3				m_position					= Vector3::Zero;

	//�h���[���邩�ۂ�
	bool				m_isDraw					= false;

	//�`�悷��^���b�g�̎��
	int					m_initDeleteSpriteNumber	= enInitDeleteTurretSprite_Null;
};