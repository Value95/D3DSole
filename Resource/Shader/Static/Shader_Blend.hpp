
texture g_AlbedoTexture;

sampler AlbedoSampler = sampler_state
{
	texture = g_AlbedoTexture;
};

texture g_ShadeTexture;

sampler ShadeSampler = sampler_state
{
	texture = g_ShadeTexture;
};

texture g_SpecularTexture;

sampler SpecularSampler = sampler_state
{
	texture = g_SpecularTexture;
};



struct PS_IN
{
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor : COLOR0;	
};

// ?ȼ? ???̴?

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	vector vAlbedo = tex2D(AlbedoSampler, In.vTexUV);
	vector vShade = tex2D(ShadeSampler, In.vTexUV);
	vector vSpecular = tex2D(SpecularSampler, In.vTexUV);

	Out.vColor = vAlbedo * vShade + vSpecular;

	return Out;
}

technique Default_Device
{
	pass	
	{
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;

		zwriteenable = false;
		vertexshader = NULL;	// ?????? ?Լ? ????
		pixelshader = compile ps_3_0 PS_MAIN();
	}
	
};