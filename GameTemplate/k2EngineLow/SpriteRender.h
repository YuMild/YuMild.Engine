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
		/// ���W��ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// �T�C�Y��ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// �T�C�Y���擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		///	��]���擾
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �s�{�b�g��ݒ�
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		/// <summary>
		/// �s�{�b�g���擾
		/// </summary>
		/// <returns></returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// �J���[��ݒ�
		/// </summary>
		/// <param name="mulColor"></param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}

		/// <summary>
		/// �J���[���擾
		/// </summary>
		/// <returns></returns>
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update()
		{
			m_sprite.Update(m_position,
				m_rotation,
				m_scale,
				m_pivot);
		}

		/// <summary>
		/// �`�揈��
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