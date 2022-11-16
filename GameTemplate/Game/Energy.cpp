#include "stdafx.h"
#include "Energy.h"

bool Energy::Start()
{
    m_windowSR.Init("Assets/Sprite/Energy/Window.dds", 404.0f, 404.0f);
    m_windowSR.SetPosition({ -450.0f,-200.0f,0.0f });
    m_windowSR.Update();
    m_circleSR.Init("Assets/Sprite/Energy/Circle.dds", 141.0f, 141.0f);
    m_circleSR.SetPosition({ -589.0f,-200.0f,0.0f });
    m_circleSR.Update();
    m_gaugeSR.Init("Assets/Sprite/Energy/Gauge.dds", 222.0f, 220.0f);
    m_gaugeSR.SetPosition({ -386.0f,-193.0f,0.0f });
    m_gaugeSR.Update();

    return true;
}

void Energy::Move()
{
    m_rotationNumber -= 1.0f;
    if (m_rotationNumber > 10000.0f)
    {
        m_rotationNumber = 0.0f;
    }
    m_rotation.SetRotationDegZ(m_rotationNumber);
    m_circleSR.SetRotation(m_rotation);
    m_circleSR.Update();
}

void Energy::Sprite()
{

}

void Energy::Update()
{
    Move();
}

void Energy::Render(RenderContext& renderContext)
{
    m_windowSR.Draw(renderContext);
    m_circleSR.Draw(renderContext);
    m_gaugeSR.Draw(renderContext);
}