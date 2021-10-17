cbuffer cbTransform : register(b0) { // 常にスロット「0」を使う
	matrix Transform;
};

struct VS_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	//float3 Col : COLOR;      // 頂点色
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	//return mul(input.Pos, Transform);
	return mul(pos, Transform);
}