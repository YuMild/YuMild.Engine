#pragma once

namespace nsK2EngineLow
{
	class SpriteRender
	{
	public:

		void Init(const char* filePath, const float width, const float height, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		void Draw(RenderContext& renderContext);

		void SetLimitedX(const float x)
		{

		}
		void SetLimitexY(const float y)
		{

		}

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// 座標を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// サイズを設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// サイズを取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		///	回転を取得
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// ピボットを設定
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		/// <summary>
		/// ピボットを取得
		/// </summary>
		/// <returns></returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// カラーを設定
		/// </summary>
		/// <param name="mulColor"></param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}

		/// <summary>
		/// カラーを取得
		/// </summary>
		/// <returns></returns>
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update()
		{
			m_sprite.Update(m_position,
				m_rotation,
				m_scale,
				m_pivot);
		}

		/// <summary>
		/// 描画処理
		/// </summary>
		/// <param name="renderContext"></param>
		void Render(RenderContext& renderContext);
		
	private:

		Sprite			m_sprite;
		Vector3			m_position = Vector3::Zero;
		Vector3			m_scale = Vector3::One;
		Quaternion		m_rotation = Quaternion::Identity;
		Vector2			m_pivot = Sprite::DEFAULT_PIVOT;
	};
}