#pragma once

class Player;

class LeftWindow : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void CursorMode();

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
		if (m_selectTurretNumber >= 7)
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

	Player*				m_player;

	SpriteRender		m_frame;
	SpriteRender		m_turretBackGround;

	Vector3				m_turretBackGroundPosition[12];

	int					m_selectTurretNumber = 0;
};