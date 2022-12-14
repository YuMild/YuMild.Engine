#pragma once

namespace nsK2EngineLow
{
	class SpriteRender
	{
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="filePath"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="alphaBlendMode"></param>
		void Init(const char* filePath, const float width, const float height, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// 画像を描画する割合を設定
		/// </summary>
		/// <param name="x"></param>
		void SetLimitedX(const float x)
		{
			m_sprite.SetX(x);
		}
		void SetLimitexY(const float y)
		{
			m_sprite.SetY(y);
		}

		/// <summary>
		/// 原点を設定。原点を元として引数の分だけ画像を生成する。
		/// Left 0.5だと左から五割だけ画像が描写される。
		/// </summary>
		/// <param name="isLeft">原点。</param>
		void SetIsDisplayRestrictionLeftSide(const bool isLeft)
		{
			m_sprite.SetIsDisplayRestrictionLeftSide(isLeft);
		}
		void SetIsDisplayRestrictionRightSide(const bool isRight)
		{
			m_sprite.SetIsDisplayRestrictionRightSide(isRight);
		}

		void SetIsDisplayRestrictionUpSide(const bool isUp)
		{
			m_sprite.SetIsDisplayRestrictionUpSide(isUp);
		}
		void SetIsDisplayRestrictionDownSide(const bool isDown)
		{
			m_sprite.SetIsDisplayRestrictionDownSide(isDown);
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