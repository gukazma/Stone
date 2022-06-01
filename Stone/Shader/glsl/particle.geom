#version 460 core
layout(points) in;
layout(points, max_vertices = 1) out;

layout (location = 0) out vec3 outValue;

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
    vec3 Pos = gl_in[0].gl_Position.xyz;
    Pos.y += u_DeltaTime;
    gl_Position = u_ViewProjection * vec4(Pos, 1.0);
    outValue = Pos;
    EmitVertex();

    EndPrimitive();
}