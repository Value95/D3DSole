matrix		g_matWorld;		
matrix		g_matView;
matrix		g_matProj;

texture		g_BaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

texture		g_BaseTexture1;

sampler BaseSampler1 = sampler_state
{
	texture = g_BaseTexture1;

	minfilter = linear;
	magfilter = linear;
};

texture		g_FilterTexture;

sampler FilterSampler = sampler_state
{
	texture = g_FilterTexture;

	minfilter = linear;
	magfilter = linear;
};

texture		g_AuraTexture;

sampler AuraSampler = sampler_state
{
	texture = g_AuraTexture;

minfilter = linear;
magfilter = linear;
};



vector g_vPlayerPos;

float	g_fPower;
float	g_fDetail;

float	g_fRange;

struct VS_IN
{
	vector		vPosition   : POSITION;	
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
};

struct VS_OUT
{
	vector		vPosition : POSITION;	
	vector		vNormal : NORMAL;
	float2		vTexUV : TEXCOORD0;
	vector		vWorldPos : TEXCOORD1;
	vector		vProjPos : TEXCOORD2;
};

// 버텍스쉐이더

VS_OUT		VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix			matWV, matWVP;

	matWV  = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);

	Out.vNormal = normalize(mul(vector(In.vNormal.xyz, 0.f), g_matWorld));
	Out.vWorldPos = mul(vector(In.vPosition.xyz, 1.f), g_matWorld);
	Out.vTexUV = In.vTexUV;
	Out.vProjPos = Out.vPosition;

	return Out;
}

struct PS_IN
{
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
	vector		vWorldPos   : TEXCOORD1;
	vector		vProjPos    : TEXCOORD2;
};

struct PS_OUT
{
	vector		vColor  : COLOR0;	
	vector		vNormal : COLOR1; 
	vector		vDepth  : COLOR2;
};

// 픽셀 쉐이더

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	vector vColor = tex2D(BaseSampler, In.vTexUV * g_fDetail);
	
	vector vColor1 = tex2D(BaseSampler1, In.vTexUV * g_fDetail);
	vector vFilter = tex2D(FilterSampler, In.vTexUV);

	Out.vColor = vColor * vFilter + vColor1 * (1.f - vFilter);
	Out.vColor.a = 1.f;

	vector		vAuraColor = (vector)0.f;

	if (g_vPlayerPos.x - g_fRange < In.vWorldPos.x &&
		g_vPlayerPos.x + g_fRange > In.vWorldPos.x &&
		g_vPlayerPos.z - g_fRange < In.vWorldPos.z &&
		g_vPlayerPos.z + g_fRange > In.vWorldPos.z)
	{
		float2 vTexUV;

		vTexUV.x = (In.vWorldPos.x - (g_vPlayerPos.x - g_fRange)) / (g_fRange * 2.f);
		vTexUV.y = ((g_vPlayerPos.z + g_fRange) - In.vWorldPos.z) / (g_fRange * 2.f);

		vAuraColor = tex2D(AuraSampler, vTexUV);
	}

	Out.vColor += vAuraColor;

	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
		
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w,	// R에 위치에 z나누기 끝난 투영 공간의 z값을 보관(0 ~ 1)값
						In.vProjPos.w * 0.001f,			// G에 위치에 far 평면의 z로 나눈 뷰스페이스의 z값을 보관(뷰스페이스 상태에서 near는 0.1로 far는 1000으로 설정한 상황) : 우리가 보관하고자 하는 형태는 컬러값(컬러값의 범위는 0~1)
						0.f, 
						0.f);
	return Out;
}

technique Default_Device
{
	pass	
	{
		vertexshader = compile vs_3_0 VS_MAIN();	
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};