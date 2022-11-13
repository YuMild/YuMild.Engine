#pragma once

class LeftWindow;
class TurretManager;

enum InitDeleteTurretSprite
{
	enInitDeleteTurretSprite_DualGunTurret,
	enInitDeleteTurretSprite_LaserTurret,
	enInitDeleteTurretSprite_RocketTurret,
	enInitDeleteTurretSprite_Null
};

class LeftWindow_Delete:public IGameObject
{
public:
	
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
	int GetTurretType() const
	{
		return m_initDeleteSpriteNumber;
	}

	/// <summary>
	/// �폜�p�̉摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="number"></param>
	/// <returns></returns>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// �폜�p�̉摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �h���[���邩�ۂ��ݒ�
	/// </summary>
	/// <param name="isDraw"></param>
	void SetIsDraw(const bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/// <summary>
	/// �h���[���邩�ۂ��擾
	/// </summary>
	/// <returns></returns>
	bool GetIsDraw()const
	{
		return m_isDraw;
	}

private:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	LeftWindow*			m_leftWindow;
	TurretManager*		m_turretManager;

	SpriteRender		m_spriteRender;

	Vector3				m_position;

	bool				m_isDraw = false;

	int					m_initDeleteSpriteNumber = enInitDeleteTurretSprite_DualGunTurret;
};