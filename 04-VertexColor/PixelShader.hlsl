struct PS_INPUT {
	float4 Pos : SV_POSITION;   // 頂点座標(モデル座標系)
	float4 Col : COLOR;      // 頂点色
};

float4 main(PS_INPUT input) : SV_TARGET
{
	return input.Col;

	//return float4(input.Col.xyz, 0.1f);
	//return float4(input.Pos.xy, 1.0f, 1.0f);
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}