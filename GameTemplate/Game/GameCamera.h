#pragma once

enum CameraState
{
	enCameraState_Normal,
	enCameraState_SetTurret,
	enCameraState_SpaceShip
};

/// <summary>
/// ゲームカメラ
/// </summary>
class GameCamera : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// カメラの位置を設定
	/// </summary>
	void SetCameraPosition(float x, float y, float z)
	{
		m_cameraPosition_X = x;
		m_cameraPosition_Y = y;
		m_cameraPosition_Z = z;
	}

	/// <summary>
	/// カメラの状態を設定
	/// </summary>
	void SetCameraState(int state)
	{
		m_cameraState = state;
	}

	/// <summary>
	/// カメラの状態を取得
	/// </summary>
	/// <returns></returns>
	int GetCameraState()
	{
		return m_cameraState;
	}

	/// <summary>
	/// カメラを揺らす
	/// </summary>
	void SetCameraShake()
	{
		m_cameraShake = true;
		m_shakeTimer = 0.0f;
	}

private:

	bool			m_cameraShake		= false;
	float			m_shakeTimer		= 0.0f;

	int				m_cameraState		= enCameraState_Normal;
	float			m_cameraTarget_Z	= 0.0f;
	float			m_cameraPosition_X	= 0.0f;
	float			m_cameraPosition_Y	= 0.0f;
	float			m_cameraPosition_Z	= 0.0f;

	//フォント
	FontRender		m_fontRenderCameraState;
	FontRender		m_fontRenderX;
	FontRender		m_fontRenderY;
	FontRender		m_fontRenderZ;
};