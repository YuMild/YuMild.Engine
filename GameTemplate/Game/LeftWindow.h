#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

class Energy;
class Game;
class GameCamera;
class LeftWindowDelete;
class Player;
class SpaceShip;
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
	const void SetOperationState(OperationState operationState)
	{
		m_operationState = operationState;
	}

	/// <summary>
	/// ����X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	const int& GetOperationState()
	{
		return m_operationState;
	}

	/// <summary>
	/// �ړ��������擾
	/// </summary>
	/// <returns></returns>
	const float& GetMoveNumber()
	{
		return m_moveNumber;
	}

	/// <summary>
	/// �J�[�\������i���
	/// </summary>
	const void TurretCursorUp()
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
	const void TurretCursorDown()
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
	const void TurretCursorRight()
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
	const void TurretCursorLeft()
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
	const int& GetSelectTurretNumber()
	{
		return m_selectTurretNumber;
	}

	/// <summary>
	/// �{�^���̃f�B���C��L��������
	/// </summary>
	const void SetButtonDelay()
	{
		m_buttonDelay = 0.0f;
	}

	/// <summary>
	/// �{�^�����g�p�\���ۂ��擾
	/// </summary>
	/// <returns></returns>
	const bool& GetButtonReady()
	{
		return m_buttonReady;
	}

	/// <summary>
	/// �E�B���h�E�؂�ւ����̉������Đ�
	/// </summary>
	void SoundPlayWindow();

	/// <summary>
	/// �I�����ڐ؂�ւ����̉������Đ�
	/// </summary>
	void SoundPlayChoice();

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
	Energy*						m_energy						= nullptr;
	GameCamera*					m_gameCamera					= nullptr;
	LeftWindowDelete*			m_leftWindowDelete				= nullptr;
	Player*						m_player						= nullptr;
	SpaceShip*					m_spaceShip						= nullptr;
	TurretManager*				m_turretManager					= nullptr;
	std::vector<TurretObject*>	m_turrets;
	std::vector<EnemyObject*>	m_enemys;

	//����
	SoundSource*				m_windowSE						= nullptr;
	SoundSource*				m_choiceSE						= nullptr;

	//���f��
	ModelRender					m_gridMR;
	ModelRender					m_gridCursorMR;
	Vector3						m_gridCursorPosition			= Vector3::Zero;

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
	//������
	SpriteRender				m_descride_NormalTurretSR;
	SpriteRender				m_descride_DualGunTurretSR;
	SpriteRender				m_descride_LaserTurretSR;
	SpriteRender				m_descride_RocketTurretSR;
	SpriteRender				m_descride_GenerationTurretSR;
	SpriteRender				m_descride_HealTurretSR;
	SpriteRender				m_descride_TeslaTurretSR;
	SpriteRender				m_descride_HolyTurretSR;
	//�w�i
	SpriteRender				m_weapons_BackGroundSR;
	SpriteRender				m_delete_BackGroundSR;
	SpriteRender				m_turret_BackGroundSR;
	//UI�A�j���[�V����
	SpriteRender				m_choiceEffectSR;

	//�w�i�̃|�W�V����
	Vector3						m_turretBackGroundPosition[12];
	//UI�A�j���[�V�����̃|�W�V����
	Vector3						m_choiceEffectPosition			= Vector3::Zero;

	//�X�e�[�g
	int							m_operationState				= enOperationState_Normal_LeftWindow;

	//�I�����Ă���^���b�g
	int							m_selectTurretNumber			= 0;

	//�{�^���̏d�����N���Ȃ��悤�f�B���C��������
	bool						m_buttonReady					= false;
	float						m_buttonDelay					= 0.0f;

	//�p�����[�^�[
	float						m_rangeNumber					= 0.0f;
	float						m_damageNumber					= 0.0f;
	float						m_fireRateNumber				= 0.0f;
	float						m_rangeSetNumber				= 0.0f;
	float						m_damageSetNumber				= 0.0f;
	float						m_fireRateSetNumber				= 0.0f;

	//�E�B���h�E�̃|�W�V�����ɉ��Z���鐔�l
	float						m_moveNumber					= 0.0f;
};