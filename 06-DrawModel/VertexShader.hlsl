cbuffer cbTransform : register(b0) { // 常にスロット「0」を使う
	matrix Transform;
};

// Slot1 View変換
cbuffer cbView : register(b1) {
	matrix View;
};

// Slot2 投影変換
cbuffer cbProjection : register(b2) {
	matrix Projection;
};

struct VS_INPUT {
	float3 Pos : POSITION;   // 頂点座標(モデル座標系)
	float4 Col : COLOR;      // 頂点色
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;
	float4 Col : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	// transのみ
	//output.Pos = mul(input.Pos, Transform);

	// ViewTrans
	//float4 pos = mul(input.Pos, Transform);
	//output.Pos = mul(pos, View);

	// ViewProjection
	float4 pos = float4(input.Pos, 1.0);
	pos = mul(pos, Transform);
	pos = mul(pos, View);
	output.Pos = mul(pos, Projection);

	output.Col = input.Col;

	return output;
}