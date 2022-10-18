#pragma once

namespace nsK2EngineLow
{
	class FontRender
	{
	public:

		/// <summary>
		/// 表示する文字を設定
		/// </summary>
		/// <param name="text"></param>
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		/// <summary>
		/// ポジションを設定
		/// </summary>
		/// <param name="position"></param>
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		/// <summary>
		/// サイズを設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}

		/// <summary>
		/// カラーを設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}

		/// <summary>
		/// 原点を設定
		/// x=0.0f y=0.0fで画像の左下
		/// x=1.0f y=1.0fで画像の右上
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}

		/// <summary>
		/// 描画処理
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