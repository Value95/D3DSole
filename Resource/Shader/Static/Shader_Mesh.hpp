matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProj;

texture		g_BaseTexture;

float       g_fAlpha;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

	minfilter = linear;
	magfilter = linear;
};

vector g_vLightDir;
vector g_vCamPos;

vector g_vLightDiffuse;
vector g_vLightSpecular;
vector g_vLightAmbient;

vector	g_vMtrlDiffuse;
vector	g_vMtrlSpecular;
vector	g_vMtrlAmbient;

float	g_fPower;
float	g_fDetail;


struct VS_IN
{
	vector		vPosition   : POSITION;	
	vector		vNormal		: NORMAL;
	float2		vTexUV		: TEXCOORD0;
	
};

struct VS_OUT
{
	vector		vPosition : POSITION;	
	vector		vShade : COLOR0;
	vector		vSpecular : COLOR1;
	float2		vTexUV : TEXCOORD0;
};

// πˆ≈ÿΩ∫Ω¶¿Ã¥ı

VS_OUT		VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix			matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);

	vector vWorldNormal = mul(vector(In.vNormal.xyz, 0.f), g_matWorld);
	vector vWorldDir = g_vLightDir * -1.f;

	float fIntensity = saturate(dot(normalize(vWorldNormal), normalize(vWorldDir)));
	// max(dot(normalize(vWorldNormal), normalize(vWorldDir), 0.f);

	Out.vShade = fIntensity;
	Out.vShade.a = 1.f;

	// Ω∫∆Â≈ß∑Ø¿« ºº±‚ ∞™ ±∏«œ±‚
	vector	vReflect = reflect(normalize(g_vLightDir), normalize(vWorldNormal));
	vector  vWorldPos = mul(vector(In.vPosition.xyz, 1.f), g_matWorld);

	vector vLook = vWorldPos - g_vCamPos;

	Out.vSpecular = pow(saturate(dot(normalize(vLook) * -1.f, normalize(vReflect))), g_fPower);
	Out.vSpecular.a = 1.f;

	Out.vTexUV = In.vTexUV;

	return Out;
}

struct PS_IN
{
	vector		vShade		: COLOR0;
	vector		vSpecular	: COLOR1;
	float2		vTexUV		: TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;
};

// «»ºø Ω¶¿Ã¥ı

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector vColor = tex2D(BaseSampler, In.vTexUV);

	Out.vColor = ((In.vShade * vColor) * (g_vLightDiffuse * g_vMtrlDiffuse)) + (g_vLightAmbient * g_vMtrlAmbient) /*+ (In.vSpecular * (g_vLightSpecular * g_vMtrlSpecular))*/;


	// Out.vColor = (vColor) * (g_vLightDiffuse * g_vMtrlDiffuse) + (In.vShade) * (g_vLightAmbient * g_vMtrlAmbient);

	// Out.vColor = (vColor) * (g_vLightDiffuse * g_vMtrlDiffuse) * ((In.vShade) + (g_vLightAmbient * g_vMtrlAmbient));
	return Out;
}

PS_OUT		PS_ALPHA(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);
		 
	return Out;
}

PS_OUT		PS_SHADE(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	Out.vColor.rgb = 0.f;
	Out.vColor.a = g_fAlpha;

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

	pass
	{
		alphablendenable = true;
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader  = compile ps_3_0 PS_SHADE();
	}

};