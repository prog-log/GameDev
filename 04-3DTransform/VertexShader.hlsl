cbuffer cbTransform : register(b0) { // ��ɃX���b�g�u0�v���g��
	matrix Transform;
};

struct VS_INPUT {
	float3 Pos : POSITION;   // ���_���W(���f�����W�n)
	//float3 Col : COLOR;      // ���_�F
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	//return mul(input.Pos, Transform);
	return mul(pos, Transform);
}