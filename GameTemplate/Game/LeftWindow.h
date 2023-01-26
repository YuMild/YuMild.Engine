#pragma once

#include "TurretObject.h"

class Energy;
class Game;
class LeftWindowDelete;
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
	/// �ړ��������擾
	/// </summary>
	/// <returns></returns>
	float GetMoveNumber()
	{
		return m_moveNumber;
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
		if (m_selectTurretNumber != 11)
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
		if (m_selectTurretNumber != 0)
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
	/// �X�y�[�X�V�b�v��p�̃J�����|�W�V�����ɂ��邩�ۂ��ݒ�
	/// </summary>
	void SetSpaceShipCameraPosition(bool value)
	{
		m_spaceShipCamera = value;
		if (m_spaceShipCamera == true)
		{
			g_camera3D->SetTarget({ 0.0f,0.0f,-1500.0f });
			g_camera3D->SetPosition({ 0.0f, 2000.0f, 2000.0f });
		}
		else
		{
			g_camera3D->SetTarget({ 0.0f,0.0f,-1500.0f });
			g_camera3D->SetPosition({ 0.0f, 3500.0f, 2000.0f });
		}
	}

	/// <summary>
	/// �E�B���h�E�؂�ւ����̉������Đ�
	/// </summary>
	void SoundPlayWindow()
	{
		m_windowSE = NewGO<SoundSource>(0);
		m_windowSE->Init(3);
		m_windowSE->SetVolume(0.3f);
		m_windowSE->Play(false);
	}

	/// <summary>
	/// �I�����ڐ؂�ւ����̉������Đ�
	/// </summary>
	void SoundPlayChoice()
	{
		m_choiceSE = NewGO<SoundSource>(0);
		m_choiceSE->Init(4);
		m_choiceSE->SetVolume(0.1f);
		m_choiceSE->Play(false);
	}

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

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
	Energy*						m_energy;
	LeftWindowDelete*			m_leftWindowDelete;
	Player*						m_player;
	TurretManager*				m_turretManager;
	std::vector<TurretObject*>	m_turrets;

	//����
	SoundSource*				m_windowSE;
	SoundSource*				m_choiceSE;

	//���f��
	ModelRender					m_gridMR;
	ModelRender					m_gridCursorMR;
	Vector3						m_gridCursorPosition;

	//�摜
	//�g
	SpriteRender				m_frameSR;
	//�p�����[�^�[
	SpriteRender				m_parameter_RangeSR;
	SpriteRender				m_parameter_DamageSR;
	SpriteRender				m_parameter_FireRateSR;
	//�ڍ�
	SpriteRender				m_detail_NormalTurretSR;
	SpriteRender				m_detail_DualGunTurretSR;
	SpriteRender				m_detail_LaserTurretSR;
	SpriteRender				m_detail_RocketTurretSR;
	SpriteRender				m_detail_GenerationTurretSR;
	SpriteRender				m_detail_HealTurretSR;
	SpriteRender				m_detail_TeslaTurretSR;
	SpriteRender				m_detail_HolyTurretSR;

	//�w�i
	SpriteRender				m_weapons_BackGroundSR;
	SpriteRender				m_delete_BackGroundSR;
	SpriteRender				m_turret_BackGroundSR;

	//�w�i�̃|�W�V����
	Vector3						m_turretBackGroundPosition[12];

	//�X�e�[�g
	int							m_operationState = enOperationState_Normal_LeftWindow;

	//�I�����Ă���^���b�g
	int							m_selectTurretNumber = 0;

	//�{�^���̏d�����N���Ȃ��悤�f�B���C��������
	bool						m_buttonReady = false;
	float						m_buttonDelay = 0.0f;

	//�p�����[�^�[
	float						m_rangeNumber = 0.0f;
	float						m_damageNumber = 0.0f;
	float						m_fireRateNumber = 0.0f;
	float						m_rangeSetNumber = 0.0f;
	float						m_damageSetNumber = 0.0f;
	float						m_fireRateSetNumber = 0.0f;

	//�E�B���h�E�̃|�W�V�����ɉ��Z���鐔�l
	float						m_moveNumber = 0.0f;

	//SpaceShip��p�̃J�����ʒu�ɂ��邩�ۂ�
	bool						m_spaceShipCamera = false;
};