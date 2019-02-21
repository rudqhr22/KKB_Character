Texture2D g_txDiffuse  : register (t0);
SamplerState sample0 : register (s0);

cbuffer cb0
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	float4	g_color1		: packoffset(c12);
};

struct VS_INPUT
{
	float4 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};


struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};



VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(vIn.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);

	output.n = vIn.n;
	output.t = vIn.t;
	output.c = g_color1; // vIn.t;
	return output;
}


float4 PS(VS_OUTPUT input) : SV_Target
{
	return g_txDiffuse.Sample(sample0, input.t);// *input.c;

}




//////////////////////////////////////////////////////////////////////////////
//
//static const int g_iNumTexure = 6;
//Texture2D g_txDiffuse: register (t0);
////�ؽ�ó �� 6��
//Texture2D g_txDiffuseArray[g_iNumTexure]: register (t1);			//->1�徿 6�� �Ѹ���
////�ؽ�û ���忡 6��
//Texture2DArray g_txDiffuseArray[g_iNumTexure]	: register (t2);	//->�ѹ��� 6�� �Ѹ���						
//
//
//
//SamplerState samLinear: register (s0);
//
//cbuffer cb0
//{
//	float4x4	g_matWorld	: packoffset(c0);
//	float4x4	g_matView	: packoffset(c4);
//	float4x4	g_matProj	: packoffset(c8);
//	float4		g_MeshColor     : packoffset(c12);
//};
//
//float4 GetSkyColor(uint index, float2 uv)
//{
//	float4 fColor = float4(1, 1, 1, 1);
//	Switch(intdex)
//	{
//		case 0 : f
//
//	}
//	return fColor;
//}
//
//
////--------------------------------------------------------------------------------------
//struct VS_INPUT
//{
//	float4 p : POSITION;
//	float3 n : NORMAL;
//	float4 c : COLOR;
//	float2 t : TEXCOORD;
//};
//
//struct VS_OUTPUT_SKY
//{
//	float4 p : SV_POSITION;
//	float3 n : NORMAL;
//	float4 c : COLOR0;
//	float2 t : TEXCOORD0;
//	uint primitiveID : SV_PrimitiveID;		//�ý����� �ﰢ�� ������ ID�� �ű���ش�.
//	//�Ƚ� ���̴� ��ǲ���� ���� �ȴ�.
//};
//
////--------------------------------------------------------------------------------------
//// Vertex Shader
////--------------------------------------------------------------------------------------
//VS_OUTPUT_SKY VS(VS_INPUT vIn)
//{
//	VS_OUTPUT output = (VS_OUTPUT)0;
//	output.p = mul(vIn.p, g_matWorld);
//	output.p = mul(output.p, g_matView);
//	output.p = mul(output.p, g_matProj);
//
//		output.p = float4 (output.x, output.y, output.x, output.w);
//
//	output.p = mul(output.p, g_matProj);
//
//float 3 
//
//	output.id
//
//	output.n = vIn.n;
//	output.t = vIn.t;
//	output.c = vIn.c * g_MeshColor;
//	return output;
//}
//
////--------------------------------------------------------------------------------------
//// Pixel Shader
////--------------------------------------------------------------------------------------
////�ؽ�ó�迭�� �ѱ�� �ȵǰ�, �ؽ�ó ��ü�� �迭ȭ�� ������ �Ѵ�.
//
//float4 PS(VS_OUTPUT_SKY vIn) : SV_Target
//{
//	uint index = vIn.id /2;		
//	float4 vColor = GetSkyColor(index);
//
//	g_txDiffuseArray.Sample(samLinear, float3(vIn.t, index));//3D�� �Ҷ�
//
//	return vColor * vIn.c;
//
//	return g_txDiffuse.Sample(samLinear, vIn.t) *vIn.c;
//}

//context->PSSetShaderResouces(1,6) t1 ���� �ؽ�ó 6��
//context->PSSetShaderResouces(3,1)	t3 ���� �ؽ�ó 1��
