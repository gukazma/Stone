#version 460 core
layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 in_Pos; 
layout (location = 1) in vec3 in_Normal; 
layout (location = 2) in vec2 in_TexCoord; 
layout (location = 3) in flat vec3 in_CameraPos; 

layout(std140, binding = 1) uniform LightBlock
{
	vec3 u_LightPos;
    vec3 u_LightAmbientColor;
    vec3 u_LightDiffuseColor;
    vec3 u_LightSpecularColor;
};


layout(std140, binding = 2) uniform MaterialBlock
{
	vec3	u_MaterialAmbient;
	vec3	u_MaterialDiffuse;
	vec3	u_MaterialSpecular;
	float	u_MaterialShininess;
};

layout (binding = 0) uniform sampler2D simple;

void main()
{
    // ambient
    vec3 ambient = u_LightAmbientColor * u_MaterialAmbient;
  	
    // diffuse 
    vec3 norm = normalize(in_Normal);
    vec3 lightDir = normalize(u_LightPos - in_Pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_MaterialDiffuse * (diff * u_MaterialDiffuse);
    
    // specular
    vec3 viewDir = normalize(in_CameraPos - in_Pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_MaterialShininess);
    vec3 specular = u_LightSpecularColor * (spec * u_MaterialSpecular);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0) * texture(simple, in_TexCoord);
}