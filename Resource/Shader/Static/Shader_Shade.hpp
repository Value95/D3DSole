texture			g_NormalTexture;

sampler NormalSampler = sampler_state
{
	texture = g_NormalTexture;
};

texture			g_DepthTexture;

sampler DepthSampler = sampler_state
{
	texture = g_DepthTexture;
};


vector			g_vLightDir;
vector			g_vLightPos;
vector			g_vLightDiffuse;
vector			g_vLightAmbient;

vector			g_vMtrlDiffuse = (vector)1.f;
vector			g_vMtrlAmbient = (vector)1.f;

vector			g_vCamPos;
float			g_fPower;
float			g_fRange;

matrix			g_matInvProj;
matrix			g_matInvView;

struct PS_IN
{
	float2	vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vShade : COLOR0;
	vector		vSpecular : COLOR1;
};

PS_OUT		PS_DIRECTIONAL(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	// �ؽ��� uv ������ ���� ����
	vector		vNormal = tex2D(NormalSampler, In.vTexUV);

	// �ؽ�ó->����
	vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);

	Out.vShade = saturate(dot(normalize(g_vLightDir) * -1.f, vNormal)) * (g_vLightDiffuse * g_vMtrlDiffuse) + (g_vLightAmbient * g_vMtrlAmbient);

	vector	vReflect = reflect(normalize(vector(g_vLightDir.xyz, 0.f)), vNormal);

	// vPosition : ���� �� �����ϴ� �ȼ��� ��ġ ��

	vector  vDepth  = tex2D(DepthSampler, In.vTexUV);
	float	fViewZ = vDepth.y * 1000.f;	// �ؽ�ó uv ���·� ����� ���� far ������ ���� �����ߴ� �佺���̽� z���� �ٽ� far���� �����༭ �����·� ����
	
	vector		vPosition;
	
	// �ؽ��� uv�� ���� ���� ������ ������ �̿��� z������ ������ ���������� �ȼ� ������ ���� ����

	// �ؽ�ó U���� ������ x������ ��ȯ 0 -> -1, 1 -> 1
	vPosition.x = (In.vTexUV.x * 2.f - 1.f) * fViewZ;
	// �ؽ�ó V���� ������ y������ ��ȯ 0 -> 1, 1 -> -1
	vPosition.y = (In.vTexUV.y * -2.f + 1.f) * fViewZ;
	vPosition.z = vDepth.x * fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matInvProj);
	vPosition = mul(vPosition, g_matInvView);
	
	vector	vLook = normalize(g_vCamPos - vPosition);

	Out.vSpecular = pow(saturate(dot(normalize(vReflect), vLook)), g_fPower);


	return Out;
}

PS_OUT		PS_POINT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	// �ؽ��� uv ������ ���� ����
	vector		vNormal = tex2D(NormalSampler, In.vTexUV);

	// vPosition : ���� �� �����ϴ� �ȼ��� ��ġ ��
	vector  vDepth = tex2D(DepthSampler, In.vTexUV);
	float	fViewZ = vDepth.y * 1000.f;	// �ؽ�ó uv ���·� ����� ���� far ������ ���� �����ߴ� �佺���̽� z���� �ٽ� far���� �����༭ �����·� ����

	vector		vPosition;

	// �ؽ��� uv�� ���� ���� ������ ������ �̿��� z������ ������ ���������� �ȼ� ������ ���� ����

	// �ؽ�ó U���� ������ x������ ��ȯ 0 -> -1, 1 -> 1
	vPosition.x = (In.vTexUV.x * 2.f - 1.f) * fViewZ;
	// �ؽ�ó V���� ������ y������ ��ȯ 0 -> 1, 1 -> -1
	vPosition.y = (In.vTexUV.y * -2.f + 1.f) * fViewZ;
	vPosition.z = vDepth.x * fViewZ;
	vPosition.w = fViewZ;

	vPosition = mul(vPosition, g_matInvProj);
	vPosition = mul(vPosition, g_matInvView);


	// �ؽ�ó->����
	vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);

	vector vLightDir = vPosition - g_vLightPos;
	float fDistance = length(vLightDir);

	float	fAtt = max((g_fRange - fDistance) / g_fRange, 0.f);

	Out.vShade = (saturate(dot(normalize(vLightDir) * -1.f, vNormal)) * (g_vLightDiffuse * g_vMtrlDiffuse) + (g_vLightAmbient * g_vMtrlAmbient)) * fAtt;
	Out.vShade.a = 1.f;

	vector	vReflect = reflect(normalize(vector(vLightDir.xyz, 0.f)), vNormal);
	vector	vLook = normalize(g_vLightPos - vPosition);

	Out.vSpecular = (pow(saturate(dot(normalize(vReflect), vLook)), g_fPower)) * fAtt;
	
	return Out;
}

technique Default_Device
{
	pass Directional
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;

		zwriteenable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_DIRECTIONAL();
	}

	pass Point
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;
		zwriteenable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_POINT();
	}

};