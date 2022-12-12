#pragma once

class LeftWindow;

/// <summary>
/// �G�l���M�[
/// </summary>
class Energy : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// �G�l���M�[��ݒ�
	/// </summary>
	/// <param name="setEnergy"></param>
	void SetEnergy(const float setEnergy)
	{
		m_energy = setEnergy;
	}

	/// <summary>
	/// �G�l���M�[���擾
	/// </summary>
	/// <param name="setEnergy"></param>
	float GetEnergy() const
	{
		return m_energy;
	}

	/// <summary>
	/// �G�l���M�[�����Z
	/// </summary>
	/// <param name="addEnergy"></param>
	/// <returns></returns>
	void AddEnergy(const float addEnergy)
	{
		m_energy += addEnergy;
	}

	/// <summary>
	/// �G�l���M�[�����Z
	/// </summary>
	/// <param name="subEnergy"></param>
	/// <returns></returns>
	void SubEnergy(const float subEnergy)
	{
		m_energy -= subEnergy;
	}

	/// <summary>
	/// �W�F�l���[�V�����^���b�g�̐������Z
	/// </summary>
	void AddGenerationTurret()
	{
		m_generationTurret += 1;
	}

	/// <summary>
	/// �W�F�l���[�V�����^���b�g�̐������Z
	/// </summary>
	void SubGenerationTurret()
	{
		m_generationTurret -= 1;
	}

	/// <summary>
	/// �R�X�g�s�����̉������Đ�
	/// </summary>
	void SoundPlayNotEnoughCost()
	{
		m_notEnoughCost = NewGO<SoundSource>(0);
		m_notEnoughCost->Init(7);
		m_notEnoughCost->SetVolume(0.05f);
		m_notEnoughCost->Play(false);
	}

private:

	/// <summary>
	/// ����̊Ǘ�
	/// </summary>
	void Move();

	/// <summary>
	/// �摜�̊Ǘ�
	/// </summary>
	void Sprite();

	/// <summary>
	/// �t�H���g�̊Ǘ�
	/// </summary>
	void Font();

	/// <summary>
	/// ����̌����̒l���擾
	/// </summary>
	float Digit(int number, int first, int end)
	{
		int powNumber;
		float result;

		//End�ȏ�̌����擾
		powNumber = number % (int)pow(10, end + 1);

		//First�ȉ��̌����擾
		result = powNumber / pow(10, first);

		return result;
	}

	//�N���X
	LeftWindow*		m_leftWindow;

	//���y
	SoundSource*	m_notEnoughCost;

	//�摜
	SpriteRender	m_windowSR;
	Vector3			m_windowPosition;
	SpriteRender	m_circleSR;
	Vector3			m_circlePosition;
	SpriteRender	m_gaugeSR;
	Vector3			m_gaugePosition;

	//�t�H���g
	FontRender		m_fontRender;

	//�G�l���M�[
	int				m_generationTurret = 0;
	float			m_energy = 0.0f;
	float			m_energyEfficiency = 0.0f;

	//��]
	float			m_rotationNumber = 0.0f;
	Quaternion		m_rotation;
};