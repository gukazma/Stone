#version 460 core
layout (location = 0) in vec3	in_Position; 
layout (location = 1) in vec3	in_Normal; 
layout (location = 2) in vec2	in_TexCoord; 
layout (location = 3) in ivec4	in_BoneIDs; 
layout (location = 4) in vec4	in_BoneWeights; 
layout (location = 5) in float	in_VertexType; 

layout (location = 0) out vec3 out_Pos; 
layout (location = 1) out vec3 out_Normal; 
layout (location = 2) out vec2 out_TexCoord; 
layout (location = 3) out flat vec3 out_CameraPos; 

layout(std140, binding = 0) uniform CameraBlock
{
	mat4 u_ViewProjection;
	vec3 u_CameraPos;
};
layout(std140, binding = 2) uniform MeshBlock
{
	mat4 model;
};
void main()
{
	out_Pos = vec3(model * vec4(in_Position, 1.0));
    gl_Position = u_ViewProjection * vec4(out_Pos, 1.0);
	out_Normal = in_Normal;
	out_TexCoord = in_TexCoord;
	out_CameraPos = u_CameraPos;
}