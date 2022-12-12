#pragma once

namespace nsK2EngineLow
{
	/// <summary>
	/// ディレクションライト
	/// </summary>
	struct DirectionLight
	{
	public:
		/// <summary>
		/// ライトの方向を設定
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(Vector3& direction)
		{
			direction.Normalize();
			m_direction = direction;
		}
		/// <summary>
		/// ライトの方向を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirection()const
		{
			return m_direction;
		}
		/// <summary>
		/// ライトのカラーを設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
	private:
		Vector3 m_direction;
		float m_pad1;
		Vector3 m_color;
		float m_pad2;
	};

	/// <summary>
	/// ポイントライト
	/// </summary>
	struct PointLight
	{
	public:
		/// <summary>
		/// ライトのポジションを設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ライトのポジションを取得
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPosition() const
		{
			return m_position;
		}
		/// <summary>
		/// ライトのカラーを設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// ライトの影響範囲を設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range)
		{
			m_range = range;
		}
	private:
		Vector3 m_position;
		float m_pad3;
		Vector3 m_color;
		float m_range;
	};

	/// <summary>
	/// スポットライト
	/// </summary>
	struct SpotLight
	{
	public:
		/// <summary>
		/// ライトのポジションを設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}
		/// <summary>
		/// ライトのカラーを設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector3& color)
		{
			m_color = color;
		}
		/// <summary>
		/// ライトの影響範囲を設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(const float& range)
		{
			m_range = range;
		}
		/// <summary>
		/// ライトの方向を設定
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(Vector3& direction)
		{
			direction.Normalize();
			m_direction = direction;
		}
		/// <summary>
		/// ライトの角度の設定
		/// </summary>
		/// <param name="angle"></param>
		void SetAngle(const float& angle)
		{
			m_angle = angle;
		}
		/// <summary>
		/// 回転を適用
		/// </summary>
		/// <param name="rotation"></param>
		void ApplyRotation(const Quaternion& rotation)
		{
			rotation.Apply(m_direction);
		}
		/// <summary>
		/// ライトの方向を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirection()const
		{
			return m_direction;
		}
	private:
		Vector3 m_position;
		float m_pad4;
		Vector3 m_color;
		float m_range;
		Vector3 m_direction;
		float m_angle;
	};

	struct Light
	{
		DirectionLight m_directionLight;
		PointLight m_pointLight;
		SpotLight m_spotLight;
		Vector3 m_ambientLight;
		float m_pad5;
		Vector3 m_eyePos;
	};

	class SceneLight
	{
	public:
		SceneLight();
		/// <summary>
		/// ライトの構造体を取得
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_light;
		}
		/// <summary>
		/// 環境光を設定
		/// </summary>
		/// <param name="color"></param>
		void SetAmbientLight(const Vector3& color)
		{
			m_light.m_ambientLight = color;
		}
		/// <summary>
		/// 視点のポジションを設定
		/// </summary>
		/// <param name="position"></param>
		void SetEyePosition(const Vector3& position)
		{
			m_light.m_eyePos = position;
		}
		/// <summary>
		/// ディレクションライトのカラーを設定
		/// </summary>
		/// <param name="color"></param>
		void SetDirectionColor(const Vector3& color)
		{
			m_light.m_directionLight.SetColor(color);
		}
		/// <summary>
		/// ディレクションライトの方向を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirectionLightDirection()const
		{
			return m_light.m_directionLight.GetDirection();
		}
		/// <summary>
		/// ポイントライトのポジションを設定する
		/// </summary>
		/// <param name="position"></param>
		void SetPointLightPosition(const Vector3& position)
		{
			m_light.m_pointLight.SetPosition(position);
		}
		/// <summary>
		/// ポイントライトのポジションを取得
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPointLightPosition()const
		{
			return m_light.m_pointLight.GetPosition();
		}
		/// <summary>
		/// スポットライトに回転を適用
		/// </summary>
		/// <param name="rotation"></param>
		void ApplySpotLightRotation(const Quaternion& rotation)
		{
			m_light.m_spotLight.ApplyRotation(rotation);
		}
		/// <summary>
		/// スポットライトの方向を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetSpotLightDirection()const
		{
			return m_light.m_spotLight.GetDirection();
		}

	private:
		Light m_light;
	};

	extern SceneLight g_sceneLight;
}