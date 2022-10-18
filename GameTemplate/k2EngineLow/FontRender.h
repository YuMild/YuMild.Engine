#pragma once

namespace nsK2EngineLow
{
	class FontRender
	{
	public:

		/// <summary>
		/// �\�����镶����ݒ�
		/// </summary>
		/// <param name="text"></param>
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		/// <summary>
		/// �|�W�V������ݒ�
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// �T�C�Y��ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// �J���[��ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}

		/// <summary>
		/// ���_��ݒ�
		/// x=0.0f y=0.0f�ŉ摜�̍���
		/// x=1.0f y=1.0f�ŉ摜�̉E��
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

	private:

		wchar_t					m_text[256];
		Vector3					m_position;
		float					m_scale;
		float					m_rotation = 0.0f;
		Vector4					m_color;
		Vector2					m_pivot;
	};
}