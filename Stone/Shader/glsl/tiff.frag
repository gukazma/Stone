#version 460 core
layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 in_Pos; 
layout (location = 1) in vec3 in_Normal; 
layout (location = 2) in vec2 in_TexCoord; 
layout (location = 3) in flat vec3 in_CameraPos; 

void main()
{
	vec4 result = vec4(0.6, 0.6, 0.6, 1.0);

	if(in_Pos.y >= 0 && in_Pos.y <= 1000)
	{
		result = vec4(0.0, 0.0, 1.0, 1.0);
	}

	if(in_Pos.y > 1000 && in_Pos.y <= 1200)
	{
		result = vec4(0.0, 1.0, 0.0, 1.0);
	}

	if(in_Pos.y > 1200 && in_Pos.y <= 1400)
	{
		result = vec4(1.0, 1.0, 0.0, 1.0);
	}

	if(in_Pos.y > 1400 && in_Pos.y <= 1600)
	{
		result = vec4(0.87, 0.6, 0.0, 1.0);
	}

	if(in_Pos.y > 1600)
	{
		result = vec4(1.0, 0.0, 0.0, 1.0);
	}

	FragColor = result;
}