cbuffer cbTransform : register(b0) { // 常にスロット「0」を使う
	matrix Transform;
};

struct VS_INPUT {
	float4 Pos : POSITION;   // 頂点座標(モデル座標系)
	float4 Col : COLOR;      // 頂点色
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 Col : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.Pos = mul(input.Pos, Transform);
	output.Col = input.Col;

	return output;
}