// YuMild.Engine

// ディレクションライト
struct DirectionLight
{
    float3 direction;       //ライトの方向
    float3 color;           //ライトのカラー
};

// ポイントライト
struct PointLight
{
    float3 position;        //位置
    float3 color;           //カラー
    float range;            //影響範囲
};

// スポットライト
struct SpotLight
{
    float3 position;        //位置
    float3 color;           //カラー
    float range;            //影響範囲
    float3 direction;       //方向
    float angle;            //角度
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////

cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

cbuffer LightCb : register(b1)
{
    DirectionLight directionLight;
    PointLight pointLight;
    SpotLight spotLight;
    float3 ambientLight;

    float3 eyePos;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////

// スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices    : BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

// 頂点シェーダーへの入力。
struct SVSIn
{
    float4 pos      : POSITION;         //モデルの頂点座標
    float3 normal   : NORMAL;           //法線
    float2 uv       : TEXCOORD0;        //UV座標
    
    float3 tangent  : TANGENT;          //接ベクトル
    float3 biNormal : BINORMAL;         //従ベクトル
    
    SSkinVSIn skinVert;                 //スキン用のデータ
};

// ピクセルシェーダーへの入力。
struct SPSIn
{
    float4 pos      : SV_POSITION;      //スクリーン空間でのピクセルの座標
    float3 normal   : NORMAL;           //法線
    float2 uv       : TEXCOORD0;        //uv座標
    float3 worldPos : TEXCOORD1;        //ワールド座標
    
    float3 tangent  : TANGENT;          //接ベクトル
    float3 biNormal : BINORMAL;         //従ベクトル
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_texture : register(t0);             //アルベドマップ
Texture2D<float4> g_normalMap : register(t1);           //法線マップ
Texture2D<float4> g_specularMap : register(t2);         //スペキュラマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //ボーン行列
sampler g_sampler : register(s0);                       //サンプラステート

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

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
    psIn.worldPos = vsIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.normal = normalize(mul(mWorld, vsIn.normal));
	
    //接ベクトルと従ベクトルをワールド行列に変換する
    psIn.tangent = normalize(mul(mWorld, vsIn.tangent));
    psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));
    
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
    float3 normal = psIn.normal;
    //法線マップからタンジェントスペースの法線をサンプリングする
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    //タンジェントスペースの法線を0~1の範囲から-1~1の範囲に復元する
    localNormal = (localNormal - 0.5f) * 2.0f;
    //タンジェントスペースの法線をワールドスペースに変換する
    normal = psIn.tangent * localNormal.x 
    + psIn.biNormal * localNormal.y 
    + normal * localNormal.z;
    
    
    
    //ディレクションライトのLambert拡散反射光とPhong鏡面反射光を計算
    //ディレクションライトのLambert拡散反射光を計算
    //ピクセルの法線とライトの方向の内積を計算して-1を乗算
    float t = dot(normal, directionLight.direction) * -1.0f;
	//内積の結果が0以下なら0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
	//拡散反射光を計算
    float3 diffuseDirectionLight = directionLight.color * t;
    
    
    
	//ディレクションライトのPhong鏡面反射光を計算
    //反射ベクトルを計算
    float3 reflectionVectorDirectionLight = reflect(directionLight.direction, normal);
    //光が当たったサーフェイスから視点に伸びるベクトルを計算
    float3 toEyeDirectionLight = eyePos - psIn.worldPos;
    toEyeDirectionLight = normalize(toEyeDirectionLight);
	//鏡面反射の強さを求める
    t = dot(reflectionVectorDirectionLight, toEyeDirectionLight);
    //内積の結果が0以下なら0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
	//鏡面反射の強さを絞る
    t = pow(t, 5.0f);
	//鏡面反射光を計算
    float3 specularDirectionLight = directionLight.color * t;
	
    
    
    //ポイントライトのLambert拡散反射光とPhong鏡面反射光を計算
    //ポイントライトのLambert拡散反射光を計算
    //サーフェイスに入射するポイントライトの光の向きを計算
    float3 pointLightDirection = psIn.worldPos - pointLight.position;
    pointLightDirection = normalize(pointLightDirection);
    //ポイントライトのLambert拡散反射光を計算
    //ピクセルの法線とライトの方向の内積を計算して-1を乗算
    t = dot(normal, pointLightDirection) * -1.0f;
    //内積の結果が0以下なら0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    //拡散反射光を計算
    float3 diffusePointLight = pointLight.color * t;
    
    
    
    //ポイントライトのPhong鏡面反射光を計算
    //反射ベクトルを計算
    float3 reflectionVectorPointLight = reflect(pointLightDirection, normal);
    //光が当たったサーフェイスから視点に伸びるベクトルを計算
    float3 toEyePointLight = eyePos - psIn.worldPos;
    toEyePointLight = normalize(toEyePointLight);
    //鏡面反射の強さを求める
    t = dot(reflectionVectorPointLight, toEyePointLight);
    //内積の結果が0以下なら0にする
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    //鏡面反射の強さを絞る
    t = pow(t, 5.0f);
    //鏡面反射光を計算
    float3 specularPointLight = pointLight.color * t;
    //距離による影響率を計算する
    float3 distance = length(psIn.worldPos - pointLight.position);
    //影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / pointLight.range * distance;
    //影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
    //影響の仕方を指数関数的にする
    affect = pow(affect, 3.0f);
    //拡散反射光と鏡面反射光に影響率を乗算して影響を弱める
    diffusePointLight *= affect;
    specularPointLight *= affect;
    //2つの反射光を合算して最終的な反射光を求める
    float3 diffseFinalLight = diffuseDirectionLight + diffusePointLight;
    float3 specularFinalLight = specularDirectionLight + specularPointLight;
    
    
    
    //スペキュラマップ
    float specularPower = g_specularMap.Sample(g_sampler, psIn.uv).r;
    specularFinalLight *= specularPower * 10.0f;
    

    
	//拡散反射と鏡面反射を足して最終的な光を求める
    float3 finalLight = diffseFinalLight + specularFinalLight + ambientLight;
	//ライトの効果を一律で上げる
    finalLight.x += 0.2f;
    finalLight.y += 0.2f;
    finalLight.z += 0.2f;
    
    
    
    float4 finalColor = g_texture.Sample(g_sampler, psIn.uv);
	
    finalColor.xyz *= finalLight;
    
    return finalColor;
}