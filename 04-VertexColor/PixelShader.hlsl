struct PS_INPUT {
	float4 Pos : SV_POSITION;   // ���_���W(���f�����W�n)
	float4 Col : COLOR;      // ���_�F
};

float4 main(PS_INPUT input) : SV_TARGET
{
	return input.Col;

	//return float4(input.Col.xyz, 0.1f);
	//return float4(input.Pos.xy, 1.0f, 1.0f);
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}