#pragma once

class Game;

/// <summary>
/// コンテナ
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
	/// 動作を管理
	/// </summary>
	void Move();

	/// <summary>
	/// 音声を再生
	/// </summary>
	void SoundPlayContainerDoor();

	/// <summary>
	/// 音声を再生
	/// </summary>
	void SoundPlayContainerShipMove();

	//クラス
	Game*			m_game					= nullptr;

	//モデル
	ModelRender		m_containerShipMR;
	ModelRender		m_containerMR;
	ModelRender		m_containerDoorMR;
	Texture			m_campEmissionMap;
	ModelRender		m_campMR;

	//サウンド
	SoundSource*	m_containerDoorSE		= nullptr;
	SoundSource*	m_containerShipMoveSE	= nullptr;
	float			m_soundSize = 0.0f;

	//モデル動作
	Vector3			m_modelPosition			= Vector3::Zero;
	float			m_moveSpeed				= 0.0f;
	Vector3			m_target				= Vector3::Zero;
	float			m_moveTimer				= 0.0f;
	Quaternion		m_doorRotation			= Quaternion::Identity;
	float			m_doorRotationValue		= 0.0f;

	//カメラ動作
	Vector3			m_cameraPosition		= Vector3::Zero;
	Vector3			m_cameraTarget			= Vector3::Zero;

	//フォント
	FontRender		m_fontRenderX;
	FontRender		m_fontRenderY;
	FontRender		m_fontRenderZ;
	FontRender		m_doorRotationFR;
};