#pragma once

class Player;

class LeftWindow : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// �E�B���h�E���\���ɂ��Ă��鎞�̓�����Ǘ�
	/// </summary>
	void NormalMode();

	/// <summary>
	/// �E�B���h�E��\�����Ă����Ԃ̓�����Ǘ�
	/// </summary>
	void CursorMode();

	/// <summary>
	/// ����X�e�[�g��ݒ�
	/// </summary>
	/// <param name="number"></param>
	void SetOperationState(const int number)
	{
		m_operationState = number;
	}

	/// <summary>
	/// �J�[�\������i���
	/// </summary>
	void TurretCursorUp()
	{
		if (m_selectTurretNumber >= 4)
		{
			m_selectTurretNumber -= 4;
		}
	}

	/// <summary>
	/// �J�[�\������i����
	/// </summary>
	void TurretCursorDown()
	{
		if (m_selectTurretNumber <= 7)
		{
			m_selectTurretNumber += 4;
		}
	}

	/// <summary>
	/// �J�[�\������i�E��
	/// </summary>
	void TurretCursorRight()
	{
		if (m_selectTurretNumber != 3 && m_selectTurretNumber != 7 && m_selectTurretNumber != 11)
		{
			m_selectTurretNumber += 1;
		}
	}

	/// <summary>
	/// �J�[�\������i����
	/// </summary>
	void TurretCursorLeft()
	{
		if (m_selectTurretNumber != 0 && m_selectTurretNumber != 4 && m_selectTurretNumber != 8)
		{
			m_selectTurretNumber -= 1;
		}
	}

	/// <summary>
	/// �I������Ă���^���b�g���擾
	/// </summary>
	/// <returns></returns>
	int GetSelectTurretNumber()
	{
		return m_selectTurretNumber;
	}

private:

	enum OparationState
	{
		enOparationStateNormal,
		enOparationStateSelectTurret,
	};

	Player*				m_player;

	SpriteRender		m_frame;
	SpriteRender		m_turretBackGround;

	Vector3				m_turretBackGroundPosition[12];

	int					m_operationState = enOparationStateNormal;
	int					m_selectTurretNumber = 0;

	float				m_move_Number = 0.0f;
};