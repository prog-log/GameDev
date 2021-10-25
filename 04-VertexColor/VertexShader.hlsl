cbuffer cbTransform : register(b0) { // 常にスロット「0」を使う
	matrix Transform;
};

struct VS_INPUT {
	float4 Pos : POSITION;   // 頂点座標(モデル座標系)
	float4 Col : COLOR;      // 頂点色
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;   // 頂点座標(モデル座標系)
	float4 Col : COLOR;      // 頂点色
};

//float4 main( float4 pos : POSITION ) : SV_POSITION
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.Pos = mul(input.Pos, Transform);
	output.Col = input.Col;
	//output.Col = float3(0.f, 1.f, 0.f);
	//return mul(pos, Transform);

	return output;
}