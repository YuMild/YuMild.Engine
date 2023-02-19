#pragma once

class LeftWindow;

#include "Game.h"

/// <summary>
/// エネルギー
/// </summary>
class Energy : public IGameObject
{
public:

	//タレットの生産コスト
	const float COST_NORMALTURRET		= 100.0f;
	const float COST_DUALGUNTURRET		= 200.0f;
	const float COST_LASERTURRET		= 200.0f;
	const float COST_ROCKETTURRET		= 300.0f;
	const float COST_GENERATIONTURRET	= 500.0f;
	const float COST_HEALTURRET			= 500.0f;
	const float COST_TESLATURRET		= 700.0f;
	const float COST_HOLYTURRET			= 1000.0f;

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// エネルギーを設定
	/// </summary>
	/// <param name="setEnergy"></param>
	const void SetEnergy(const float setEnergy)
	{
		m_energy = setEnergy;
	}

	/// <summary>
	/// エネルギーを取得
	/// </summary>
	/// <param name="setEnergy"></param>
	const float& GetEnergy() const
	{
		return m_energy;
	}

	/// <summary>
	/// エネルギーを加算
	/// </summary>
	/// <param name="addEnergy"></param>
	/// <returns></returns>
	const void AddEnergy(const float addEnergy)
	{
		m_energy += addEnergy;
	}

	/// <summary>
	/// エネルギーを除算
	/// </summary>
	/// <param name="subEnergy"></param>
	/// <returns></returns>
	const void SubEnergy(const float subEnergy)
	{
		m_energy -= subEnergy;
	}

	/// <summary>
	/// ジェネレーションタレットの数を加算
	/// </summary>
	const void AddGenerationTurret()
	{
		m_generatorTurret += 1;
	}

	/// <summary>
	/// ジェネレーションタレットの数を減算
	/// </summary>
	const void SubGenerationTurret()
	{
		m_generatorTurret -= 1;
	}

	/// <summary>
	/// コスト不足時の音声を再生
	/// </summary>
	const void SoundPlayNotEnoughCost()
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
	LeftWindow*		m_leftWindow		= nullptr;

	//音楽
	SoundSource*	m_notEnoughCost		= nullptr;

	//画像
	SpriteRender	m_windowSR;
	Vector3			m_windowPosition	= Vector3::Zero;
	SpriteRender	m_circleSR;
	Vector3			m_circlePosition	= Vector3::Zero;
	SpriteRender	m_gaugeSR;
	Vector3			m_gaugePosition		= Vector3::Zero;

	//フォント
	FontRender		m_fontRender;

	//エネルギー
	int				m_generatorTurret	= 0;
	float			m_energy			= 0.0f;
	float			m_energyEfficiency	= 0.0f;

	//回転
	float			m_rotationNumber	= 0.0f;
	Quaternion		m_rotation			= Quaternion::Identity;
};