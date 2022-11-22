#pragma once

class LeftWindow;

/// <summary>
/// エネルギー
/// </summary>
class Energy : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// エネルギーを加算
	/// </summary>
	/// <param name="addEnergy"></param>
	/// <returns></returns>
	void AddEnergy(const float addEnergy)
	{
		m_energy += addEnergy;
	}

	/// <summary>
	/// エネルギーを除算
	/// </summary>
	/// <param name="subEnergy"></param>
	/// <returns></returns>
	void SubEnergy(const float subEnergy)
	{
		m_energy -= subEnergy;
	}

private:

	/// <summary>
	/// 動作の管理
	/// </summary>
	void Move();

	/// <summary>
	/// 画像の管理
	/// </summary>
	void Sprite();

	/// <summary>
	/// フォントの管理
	/// </summary>
	void Font();

	/// <summary>
	/// 特定の桁数の値を取得
	/// </summary>
	float Digit(int number, int first, int end)
	{
		int powNumber;
		float result;

		//End以上の桁を取得
		powNumber = number % (int)pow(10, end + 1);

		//First以下の桁を取得
		result = powNumber / pow(10, first);

		return result;
	}

	//クラス
	LeftWindow*		m_leftWindow;

	//画像
	SpriteRender	m_windowSR;
	Vector3			m_windowPosition;
	SpriteRender	m_circleSR;
	Vector3			m_circlePosition;
	SpriteRender	m_gaugeSR;
	Vector3			m_gaugePosition;

	//フォント
	FontRender		m_fontRender;

	//エネルギー
	float			m_energy = 0.0f;

	float			m_energyEfficiency = 0.0f;

	//回転
	float			m_rotationNumber = 0.0f;
	Quaternion		m_rotation;
};