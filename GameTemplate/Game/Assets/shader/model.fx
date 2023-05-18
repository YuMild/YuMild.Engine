// YuMild.Engine


////////////////////////////////////////////////
// 定数
////////////////////////////////////////////////

static const float PI = 3.1415926f; // 円周率

// ディレクションライト
struct DirectionLight
{
    float3          direction;          // 方向
    float3          color;              // カラー
};

// ポイントライト
struct PointLight
{
    float3          position;           // 位置
    float3          color;              // カラー
    float           range;              // 影響範囲
};

// スポットライト
struct SpotLight
{
    float3          position;           // 位置
    float3          color;              // カラー
    float           range;              // 影響範囲
    float3          direction;          // 方向
    float           angle;              // 角度
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////

cbuffer ModelCb : register(b0)
{
    float4x4        mWorld;
    float4x4        mView;
    float4x4        mProj;
};

cbuffer LightCb : register(b1)
{
    DirectionLight  directionLight;
    PointLight      pointLight;
    SpotLight       spotLight;
    float3          ambientLight;

    float3          eyePos;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////

// スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4            Indices      : BLENDINDICES0;
    float4          Weights      : BLENDWEIGHT0;
};

// 頂点シェーダーへの入力。
struct SVSIn
{
    float4          pos          : POSITION;        // モデルの頂点座標
    float3          normal       : NORMAL;          // 法線
    float2          uv           : TEXCOORD0;       // UV座標
    
    float3          tangent      : TANGENT;         // 接ベクトル
    float3          biNormal     : BINORMAL;        // 従ベクトル
    
    SSkinVSIn       skinVert;                       // スキン用のデータ
};

// ピクセルシェーダーへの入力。
struct SPSIn
{
    float4          pos          : SV_POSITION;     // スクリーン空間でのピクセルの座標
    float3          normal       : NORMAL;          // 法線
    float2          uv           : TEXCOORD0;       // uv座標
    float3          worldPos     : TEXCOORD1;       // ワールド座標
    
    float3          tangent      : TANGENT;         // 接ベクトル
    float3          biNormal     : BINORMAL;        // 従ベクトル
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////

Texture2D<float4>           g_albedo : register(t0);                // アルベドマップ
Texture2D<float4>           g_normalMap : register(t1);             // 法線マップ
Texture2D<float4>           g_metallicSmoothMap : register(t2);     // スペキュラマップ
StructuredBuffer<float4x4>  g_boneMatrix : register(t3);            // ボーン行列
sampler                     g_sampler : register(s0);               // サンプラステート
Texture2D<float4>           g_emission : register(t12);             // エミッション

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

// 法線を取得
float3 GetNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 binSpaceNormal = g_normalMap.SampleLevel(g_sampler, uv, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;

    float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

    return newNormal;
}

// ベックマン分布を計算する
float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

// フレネルを計算。Schlick近似を使用
float SpcFresnel(float f0, float u)
{
    // from Schlick
    return f0 + (1 - f0) * pow(1 - u, 5);
}

/// <summary>
/// Cook-Torranceモデルの鏡面反射を計算
/// </summary>
/// <param name="L">光源に向かうベクトル</param>
/// <param name="V">視点に向かうベクトル</param>
/// <param name="N">法線ベクトル</param>
/// <param name="metallic">金属度</param>
float CookTorranceSpecular(float3 L, float3 V, float3 N, float metallic)
{
    float microfacet = 0.76f;

    // 金属度を垂直入射の時のフレネル反射率として扱う
    // 金属度が高いほどフレネル反射は大きくなる
    float f0 = metallic;

    // ライトに向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
    float3 H = normalize(L + V);

    // 各種ベクトルがどれくらい似ているかを内積を利用して求める
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));

    // D項をベックマン分布を用いて計算する
    float D = Beckmann(microfacet, NdotH);

    // F項をSchlick近似を用いて計算する
    float F = SpcFresnel(f0, VdotH);

    // G項を求める
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

    // m項を求める
    float m = PI * NdotV * NdotH;

    // ここまで求めた、値を利用して、Cook-Torranceモデルの鏡面反射を求める
    return max(F * D * G / m, 0.0);
}

/// <summary>
/// フレネル反射を考慮した拡散反射を計算
/// </summary>
/// <remark>
/// この関数はフレネル反射を考慮した拡散反射率を計算します
/// フレネル反射は、光が物体の表面で反射する現象のとこで、鏡面反射の強さになります
/// 一方拡散反射は、光が物体の内部に入って、内部錯乱を起こして、拡散して反射してきた光のことです
/// つまりフレネル反射が弱いときには、拡散反射が大きくなり、フレネル反射が強いときは、拡散反射が小さくなります
/// </remark>
/// <param name="N">法線</param>
/// <param name="L">光源に向かうベクトル。光の方向と逆向きのベクトル。</param>
/// <param name="V">視線に向かうベクトル。</param>
float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
    // ディズニーベースのフレネル反射による拡散反射を真面目に実装する。
    // 光源に向かうベクトルと視線に向かうベクトルのハーフベクトルを求める
    float3 H = normalize(L + V);

    // 粗さは0.5で固定。
    float roughness = 0.5f;

    float energyBias = lerp(0.0f, 0.5f, roughness);
    float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

    // 光源に向かうベクトルとハーフベクトルがどれだけ似ているかを内積で求める
    float dotLH = saturate(dot(L, H));

    // 光源に向かうベクトルとハーフベクトル、
    // 光が平行に入射したときの拡散反射量を求めている
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;

    // 法線と光源に向かうベクトルwを利用して拡散反射率を求める
    float dotNL = saturate(dot(N, L));
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    // 法線と視点に向かうベクトルを利用して拡散反射率を求める
    float dotNV = saturate(dot(N, V));
    float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

    // 法線と光源への方向に依存する拡散反射率と、法線と視点ベクトルに依存する拡散反射率を
    // 乗算して最終的な拡散反射率を求めている。PIで除算しているのは正規化を行うため
    return (FL * FV * energyFactor);
}

/// <summary>
// スキン行列を計算する
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.normal = normalize(mul(m, vsIn.normal));
	
    //接ベクトルと従ベクトルをワールド行列に変換する
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
    
    psIn.uv = vsIn.uv;

    return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}

/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{ 
    // PBR
    // 法線を計算
    float3 normal = GetNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);
    
    // アルベドカラー（拡散反射光）
    float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
    
    // スペキュラカラーはアルベドカラーと同じにする
    float3 specColor = albedoColor;
    
    // 金属度
    float metallic = g_metallicSmoothMap.Sample(g_sampler, psIn.uv).r;
   
    // 滑らかさ
    float smooth = g_metallicSmoothMap.Sample(g_sampler, psIn.uv).a;

    // エミッション
    float3 emission = g_emission.Sample(g_sampler, psIn.uv);

    // 視線に向かって伸びるベクトルを計算する
    float3 toEye = normalize(eyePos - psIn.worldPos);
    
    // フレネル反射を考慮した拡散反射を計算
    float diffuseFromFresnel = CalcDiffuseFromFresnel(
            normal, -directionLight.direction, toEye);
    
    // 正規化Lambert拡散反射を求める
    float NdotL = saturate(dot(normal, -directionLight.direction));
    float3 lambertDiffuse = directionLight.color * NdotL / PI;
    
    // 最終的な拡散反射光を計算する
    float3 diffuse = albedoColor * diffuseFromFresnel * lambertDiffuse;

    // Cook-Torranceモデルの鏡面反射率を計算する
    float3 specular = CookTorranceSpecular(
            -directionLight.direction, toEye, normal, smooth)
            * directionLight.color;

    // 金属度が高ければ、鏡面反射はスペキュラカラー、低ければ白
    // スペキュラカラーの強さを鏡面反射率として扱う
    specular *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, metallic);

    // 滑らかさを使って、拡散反射光と鏡面反射光を合成する
    // 滑らかさが高ければ、拡散反射は弱くなる
    float3 finalLight = diffuse * (1.0f - smooth) + specular;
    
    // 環境光を加算する
    finalLight += ambientLight * albedoColor;

    // 最終カラーを求める
    float4 finalColor = 1.0f;
    finalColor.xyz *= finalLight;
    finalColor.xyz += emission * 5.0f;
    
    return finalColor;
}