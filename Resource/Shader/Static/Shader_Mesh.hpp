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
	vector		vProjPos : TEXCOORD1;
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
		
	Out.vTexUV = In.vTexUV;

	Out.vProjPos = Out.vPosition;

	return Out;
}

struct PS_IN
{
	vector		vNormal : NORMAL;
	float2		vTexUV		: TEXCOORD0;
	vector		vProjPos : TEXCOORD1;
};

struct PS_OUT
{
	vector		vColor : COLOR0;	
	vector		vNormal : COLOR1;
	vector		vDepth : COLOR2;
	
};

// 픽셀 쉐이더

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	// -1 ~ 1 -> 0 ~ 1
	// 단위 벡터 상태인 월드의 법선 값을 텍스쳐 uv 값으로 강제 변환
	Out.vNormal = vector(In.vNormal.xyz * 0.5f + 0.5f, 0.f);
	
	Out.vDepth = vector(In.vProjPos.z / In.vProjPos.w,	// R에 위치에 z나누기 끝난 투영 공간의 z값을 보관(0 ~ 1)값
		In.vProjPos.w * 0.001f,			// G에 위치에 far 평면의 z로 나눈 뷰스페이스의 z값을 보관(뷰스페이스 상태에서 near는 0.1로 far는 1000으로 설정한 상황) : 우리가 보관하고자 하는 형태는 컬러값(컬러값의 범위는 0~1)
		0.f,
		0.f);

	return Out;
}

PS_OUT		PS_ALPHA(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);
		 
	return Out;
}

technique Default_Device
{
	pass	
	{
		vertexshader = compile vs_3_0 VS_MAIN();	
		pixelshader = compile ps_3_0 PS_MAIN();
	}

	pass Alpha
	{
		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0xc0;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_ALPHA();
	}

};