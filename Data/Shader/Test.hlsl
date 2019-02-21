Texture2D g_txDiffuse  : register (t0);		//�ؽ�ó ����0
SamplerState sample0   : register (s0);		//���÷� ����0

cbuffer cb0
{
	float Color : packoffset(c0);
	float fTime : packoffset(c1.x);
}


struct VS_INPUT
{
	float4 p : POSITION;
//	float4 c : COLOR;
	float2 t : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 p : SV_POSITION;
//	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


VS_OUTPUT VS(VS_INPUT Input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = Input.p;
	//output.p = Input.c;
	output.t = Input.t;// *fTime;
	return output;
}


float4 PS(VS_OUTPUT input) : SV_Target
{
	return  g_txDiffuse.Sample(sample0, input.t);
}




//���ø� ǥ���� ���� �Ѵ�.
//������ ���� ���̿� �ش��ϴ� �ȼĵ� -> �ȼ��� ���� ���� uv���� ĳġ�س���.
//
//���͸� - �ȼ��� �ȼ������� ����
//1.�ֱ���  - ���� ������ �ȼ��� ���
//2.���� - �������� ���͸� (�߰����� ã�Ƽ� �����ϰڴ�)	//������ ����� ����� �̻��Ҽ� �ִ�.
// �տ��� �ȼ� �� ������ũ���� �ָ� �� ���� ������ �۾�����. �׷��� ��������� �޶��� �� �ۿ� ����.
//3.�̹漺 ���͸� - ���� ���� ����� ���� �Ѱ�()


//���͸��� ������ �ȵ���,
//MIN ��� 
//MAG Ȯ��
//MIP �θ�

//���÷� - ��� ���ø��� �Ұ��ΰ�.

//WRAP
//x���� y���� z����