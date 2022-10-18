#pragma once

class DualGunTurret : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// ポジションを設定
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	Vector3 SetPosition(const Vector3& position)
	{
		m_position = position;
		return position;
	}

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

private:

	ModelRender		m_modelRender;

	Vector3			m_position;
};