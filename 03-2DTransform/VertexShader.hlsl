cbuffer cb2DTransform : register(b0) { // ��ɃX���b�g�u0�v���g��
	matrix Transform;
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return mul(pos, Transform);
}