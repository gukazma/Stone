#version 460 core
layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 in_Pos; 
layout (location = 1) in vec3 in_Normal; 
layout (location = 2) in vec2 in_TexCoord; 
layout (location = 3) in flat vec3 in_CameraPos; 

layout(std140, binding = 1) uniform LightBlock
{
	vec3 u_LightPos;
};
layout (binding = 0) uniform sampler2D simple;

layout(std140, binding = 3) uniform Line
{
	int isLine;
};
void main()
{
	if(isLine==0)
	{
		vec3 n = normalize(in_Normal);
		vec4 diffuse = vec4(0.0);
		vec4 specular = vec4(0.0);
	
		// the material properties are embedded in the shader (for now)
		vec4 mat_ambient = vec4(1.0, 1.0, 1.0, 1.0);
		vec4 mat_diffuse = vec4(1.0, 1.0, 1.0, 1.0);
		vec4 mat_specular = vec4(1.0, 1.0, 1.0, 1.0);
	
		// ambient term
		vec4 ambient = mat_ambient * 0.4;
	
		// diffuse color
		vec4 kd = mat_diffuse * 0.6;
	
		// specular color
		vec4 ks = mat_specular * 0.1;
	
		// diffuse term
		vec3 lightDir = normalize(u_LightPos - in_Pos);
		float NdotL = dot(n, lightDir);
	
		if (NdotL > 0.0)
			diffuse = kd * NdotL;
	
		// specular term
		vec3 rVector = normalize(2.0 * n * dot(n, lightDir) - lightDir);
		vec3 viewVector = normalize(-in_Pos);
		float RdotV = dot(rVector, viewVector);
	
		if (RdotV > 0.0)
			specular = ks * pow(RdotV, 0.6);

		FragColor = ambient + diffuse + specular;
	}
	else
	{
		FragColor = vec4( 1.0, 1.0, 0.0, 1.0 );
	}
    
}