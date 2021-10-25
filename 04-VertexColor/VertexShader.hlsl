cbuffer cbTransform : register(b0) { // ��ɃX���b�g�u0�v���g��
	matrix Transform;
};

struct VS_INPUT {
	float4 Pos : POSITION;   // ���_���W(���f�����W�n)
	float4 Col : COLOR;      // ���_�F
};

struct VS_OUTPUT {
	float4 Pos : SV_POSITION;   // ���_���W(���f�����W�n)
	float4 Col : COLOR;      // ���_�F
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