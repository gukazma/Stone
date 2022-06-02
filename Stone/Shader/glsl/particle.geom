#version 460 core
layout(points) in;
layout(points, max_vertices = 1) out;

layout (location = 0) in float  in_Type[]; 
layout (location = 1) in vec3   in_Position[]; 

layout (location = 0) out float out_Type;
layout (location = 1) out vec3  out_Position;

layout(std140, binding = 4) uniform RendererUniformBuffer
{
	float u_DeltaTime;
};

layout(std140, binding = 0) uniform CameraBlock
{
	mat4 u_ViewProjection;
	vec3 u_CameraPos;
};


void main()
{
    vec3 Pos = in_Position[0];
    Pos.y += u_DeltaTime;
    gl_Position = u_ViewProjection * vec4(Pos, 1.0);
    out_Position = Pos;
    out_Type = in_Type[0];
    EmitVertex();

    EndPrimitive();
}