cbuffer cbTransform : register(b0) { // 常にスロット「0」を使う
	matrix Transform;
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return mul(pos, Transform);
}