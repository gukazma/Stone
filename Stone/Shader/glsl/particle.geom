#version 460 core
layout(points) in;
layout(points, max_vertices = 1) out;

layout (location = 0) in float  in_Type[]; 
layout (location = 1) in vec3   in_Position[]; 
layout (location = 2) in vec3   in_Velocity[]; 
layout (location = 3) in float  in_Age[]; 

layout (location = 0) out float     out_Type; 
layout (location = 1) out vec3      out_Position; 
layout (location = 2) out vec3      out_Velocity; 
layout (location = 3) out float     out_Age; 

layout (binding = 0) uniform sampler1D randomTexture;

layout(std140, binding = 4) uniform RendererUniformBuffer
{
	float u_DeltaTime;
	float u_GlobalTime;
};

layout(std140, binding = 0) uniform CameraBlock
{
	mat4 u_ViewProjection;
	vec3 u_CameraPos;
};

vec3 GetRandomDir(float TexCoord)                                                   
{                                                                                   
     vec3 Dir = texture(randomTexture, TexCoord).xyz;
     Dir -= vec3(0.5, 0.5, 0.5);
     return Dir;                                                                    
}              


void main()
{
    vec3 Pos = in_Position[0];
    Pos += GetRandomDir(u_GlobalTime/1000.0) * u_DeltaTime;
    gl_Position = u_ViewProjection * vec4(Pos, 1.0);
    out_Position = Pos;
    out_Type = in_Type[0];
    out_Velocity = in_Velocity[0];
    out_Age = in_Age[0];
    EmitVertex();

    EndPrimitive();
}