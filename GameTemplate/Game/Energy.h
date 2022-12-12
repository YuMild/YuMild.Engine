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
	/// エネルギーを設定
	/// </summary>
	/// <param name="setEnergy"></param>
	void SetEnergy(const float setEnergy)
	{
		m_energy = setEnergy;
	}

	/// <summary>
	/// エネルギーを取得
	/// </summary>
	/// <param name="setEnergy"></param>
	float GetEnergy() const
	{
		return m_energy;
	}

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

	/// <summary>
	/// ジェネレーションタレットの数を加算
	/// </summary>
	void AddGenerationTurret()
	{
		m_generationTurret += 1;
	}

	/// <summary>
	/// ジェネレーションタレットの数を減算
	/// </summary>
	void SubGenerationTurret()
	{
		m_generationTurret -= 1;
	}

	/// <summary>
	/// コスト不足時の音声を再生
	/// </summary>
	void SoundPlayNotEnoughCost()
	{
		m_notEnoughCost = NewGO<SoundSource>(0);
		m_notEnoughCost->Init(7);
		m_notEnoughCost->SetVolume(0.05f);
		m_notEnoughCost->Play(false);
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

	//音楽
	SoundSource*	m_notEnoughCost;

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
	int				m_generationTurret = 0;
	float			m_energy = 0.0f;
	float			m_energyEfficiency = 0.0f;

	//回転
	float			m_rotationNumber = 0.0f;
	Quaternion		m_rotation;
};