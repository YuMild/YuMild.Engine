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
	float			m_energy = 0.0f;

	float			m_energyEfficiency = 0.0f;

	//��]
	float			m_rotationNumber = 0.0f;
	Quaternion		m_rotation;
};