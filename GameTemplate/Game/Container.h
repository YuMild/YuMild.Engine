#pragma once

class Game;

/// <summary>
/// �R���e�i
/// </summary>
class Container : public IGameObject
{
public:

	~Container();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

private:

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	/// <summary>
	/// �������Đ�
	/// </summary>
	void SoundPlayContainerDoor();

	/// <summary>
	/// �������Đ�
	/// </summary>
	void SoundPlayContainerShipMove();

	//�N���X
	Game*			m_game					= nullptr;

	//���f��
	ModelRender		m_containerShipMR;
	ModelRender		m_containerMR;
	ModelRender		m_containerDoorMR;
	Texture			m_campEmissionMap;
	ModelRender		m_campMR;

	//�T�E���h
	SoundSource*	m_containerDoorSE		= nullptr;
	SoundSource*	m_containerShipMoveSE	= nullptr;
	float			m_soundSize = 0.0f;

	//���f������
	Vector3			m_modelPosition			= Vector3::Zero;
	float			m_moveSpeed				= 0.0f;
	Vector3			m_target				= Vector3::Zero;
	float			m_moveTimer				= 0.0f;
	Quaternion		m_doorRotation			= Quaternion::Identity;
	float			m_doorRotationValue		= 0.0f;

	//�J��������
	Vector3			m_cameraPosition		= Vector3::Zero;
	Vector3			m_cameraTarget			= Vector3::Zero;

	//�t�H���g
	FontRender		m_fontRenderX;
	FontRender		m_fontRenderY;
	FontRender		m_fontRenderZ;
	FontRender		m_doorRotationFR;
};