#include "stdafx.h"
#include "Energy.h"

#include "LeftWindow.h"

namespace
{
    float DEFAULT_ENERGY_EFFICIENCY = 10.0f;
}

bool Energy::Start()
{
    //FindGO
    m_leftWindow = FindGO<LeftWindow>("leftWindow");

    //フォント
    m_fontRender.SetColor({ 0.3f,0.9f,1.0f,1.0f });
    m_fontRender.SetScale(1.0f);
    m_fontRender.SetPivot(1.0f, 0.5f);
    m_fontRender.SetPosition({ 370.0,-218.0f,0.0f });

    //画像
    m_windowSR.Init("Assets/Sprite/Energy/Window.dds", 404.0f, 404.0f);
    m_windowPosition = { 489.0f,-200.0f,0.0f };
    m_windowSR.SetPosition(m_windowPosition);
    m_windowSR.Update();
    m_circleSR.Init("Assets/Sprite/Energy/Circle.dds", 141.0f, 141.0f);
    m_circlePosition = { 350.0f,-200.0f,0.0f };
    m_circleSR.SetPosition(m_circlePosition);
    m_circleSR.Update();
    m_gaugeSR.Init("Assets/Sprite/Energy/Gauge.dds", 222.0f, 220.0f);
    m_gaugePosition = { 553.0,-193.0f,0.0f };
    m_gaugeSR.SetPosition(m_gaugePosition);
    m_gaugeSR.Update();

    //エネルギー効率
    m_energyEfficiency = DEFAULT_ENERGY_EFFICIENCY;

    return true;
}

void Energy::Move()
{
    //1秒×生産効率でエネルギーを加算
    m_energy += g_gameTime->GetFrameDeltaTime() * m_energyEfficiency;

    //ジェネレーションタレットの数分効率を上げる
    m_energyEfficiency = DEFAULT_ENERGY_EFFICIENCY + (m_generationTurret / 2.0f) * 10.0f;
}

void Energy::Sprite()
{
    //ゲージ
    m_gaugeSR.SetIsDisplayRestrictionRightSide(true);
    m_gaugeSR.SetLimitedX(Digit(m_energy, 0, 1) / 100.0f);

    //サークル
    m_rotationNumber -= m_energyEfficiency / 50.0f;
    if (m_rotationNumber > 10000.0f)
    {
        m_rotationNumber = 0.0f;
    }
    m_rotation.SetRotationDegZ(m_rotationNumber);
    m_circleSR.SetRotation(m_rotation);
    m_circleSR.Update();
}

void Energy::Font()
{
    wchar_t enargy[256];
    swprintf_s(enargy, 256, L"%04d", int(m_energy));
    m_fontRender.SetText(enargy);
}

void Energy::Update()
{
    Move();
    Sprite();
    Font();
}

void Energy::Render(RenderContext& renderContext)
{
    //画像
    m_windowSR.Draw(renderContext);
    m_circleSR.Draw(renderContext);
    m_gaugeSR.Draw(renderContext);

    //フォント
    m_fontRender.Draw(renderContext);
}