#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

namespace nsK2EngineLow
{
	void FontRender::Draw(RenderContext& rc)
	{
		if (m_text == nullptr)
		{
			return;
		}
		g_renderingEngine.AddFontRenderObject(this);
	}

	void FontRender::Render(RenderContext& renderContext)
	{
		m_font.Begin(renderContext);
		m_font.Draw(m_text, Vector2(m_position.x, m_position.y), m_color, m_rotation, m_scale, m_pivot);
		m_font.End(renderContext);
	}
}