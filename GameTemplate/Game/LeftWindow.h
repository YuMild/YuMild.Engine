#pragma once

class Player;
class TurretManager;

enum OperationState
{
	enOperationState_Normal_LeftWindow,
	enOperationState_SelectTurret_LeftWindow,
	enOperationState_SetTurret_LeftWindow,
	enOperationState_Delete_LeftWindow,
	enOperationState_DeleteCheck_LeftWindow
};

class LeftWindow : public IGameObject
{
public:

	/// <summary>
	/// ����X�e�[�g��ݒ�
	/// </summary>
	/// <param name="number"></param>
	void SetOperationState(OperationState operationState)
	{
		m_operationState = operationState;
	}

	/// <summary>
	/// ����X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	int GetOperationState()
	{
		return m_operationState;
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
		SoundPlayChoice();
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
		SoundPlayChoice();
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
		SoundPlayChoice();
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
		SoundPlayChoice();
	}

	/// <summary>
	/// �I������Ă���^���b�g���擾
	/// </summary>
	/// <returns></returns>
	int GetSelectTurretNumber()
	{
		return m_selectTurretNumber;
	}

	/// <summary>
	/// �{�^���̃f�B���C��L��������
	/// </summary>
	void SetButtonDelay()
	{
		m_buttonDelay = 0.0f;
	}

	/// <summary>
	/// �{�^�����g�p�\���ۂ��擾
	/// </summary>
	/// <returns></returns>
	bool GetButtonReady()
	{
		return m_buttonReady;
	}

	/// <summary>
	/// �E�B���h�E�؂�ւ����̉������Đ�
	/// </summary>
	void SoundPlayWindow()
	{
		m_windowSE = NewGO<SoundSource>(1);
		m_windowSE->Init(1);
		m_windowSE->SetVolume(1.0f);
		m_windowSE->Play(false);
	}

	/// <summary>
	/// �I�����ڐ؂�ւ����̉������Đ�
	/// </summary>
	void SoundPlayChoice()
	{
		m_choiceSE = NewGO<SoundSource>(2);
		m_choiceSE->Init(2);
		m_choiceSE->SetVolume(0.1f);
		m_choiceSE->Play(false);
	}

private:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// �ʏ펞
	/// </summary>
	void OperationNormal();

	/// <summary>
	/// �^���b�g�I����
	/// </summary>
	void OperationSelectTurret();

	/// <summary>
	/// �^���b�g�쐬��
	/// </summary>
	void OperationSetTurret();

	/// <summary>
	/// �^���b�g�폜��
	/// </summary>
	void OperationDelete();

	/// <summary>
	/// �^���b�g�폜�m�F��
	/// </summary>
	void OperationDeleteCheck();

	/// <summary>
	/// �p�����[�^�[�o�[���Ǘ�
	/// </summary>
	void SetParameterBar();

	//�N���X
	Player*				m_player;
	TurretManager*		m_turretManager;

	//����
	SoundSource*		m_windowSE;
	SoundSource*		m_choiceSE;

	//�O���b�h
	ModelRender			m_gridMR;

	//�g
	SpriteRender		m_frameSR;
	//�p�����[�^�[
	SpriteRender		m_parameter_RangeSR;
	SpriteRender		m_parameter_DamageSR;
	SpriteRender		m_parameter_FireRateSR;
	//�ڍ�
	SpriteRender		m_dualGunTurret_DetailSR;
	SpriteRender		m_laserTurret_DetailSR;
	SpriteRender		m_rocketTurret_DetailSR;
	//�w�i
	SpriteRender		m_weapons_BackGroundSR;
	SpriteRender		m_delete_BackGroundSR;
	SpriteRender		m_turret_BackGroundSR;

	//�w�i�̃|�W�V����
	Vector3				m_turretBackGroundPosition[12];

	//�X�e�[�g
	int					m_operationState = enOperationState_Normal_LeftWindow;

	//�I�����Ă���^���b�g
	int					m_selectTurretNumber = 0;

	//�{�^���̏d�����N���Ȃ��悤�f�B���C��������
	bool				m_buttonReady = false;
	float				m_buttonDelay = 0.0f;

	//�p�����[�^�[
	float				m_rangeNumber = 0.0f;
	float				m_damageNumber = 0.0f;
	float				m_fireRateNumber = 0.0f;
	float				m_rangeSetNumber = 0.0f;
	float				m_damageSetNumber = 0.0f;
	float				m_fireRateSetNumber = 0.0f;

	//�E�B���h�E�̃|�W�V�����ɉ��Z���鐔�l
	float				m_move_Number = 0.0f;
};