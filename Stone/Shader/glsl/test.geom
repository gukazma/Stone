#version 460 core
layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

layout (location = 0) out vec2 out_TexCoord; 
layout(std140, binding = 2) uniform MeshBlock
{
	mat4 model;
};

layout(std140, binding = 0) uniform CameraBlock
{
	mat4 u_ViewProjection;
	vec3 u_CameraPos;
};


void main()
{
    vec3 Pos = gl_in[0].gl_Position.xyz;
    vec3 toCamera = normalize(u_CameraPos - Pos);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(toCamera, up);
    Pos -= (right * 0.5);
    gl_Position = u_ViewProjection * model * vec4(Pos, 1.0);
    out_TexCoord = vec2(0.0, 0.0);
    EmitVertex();

    Pos.y += 1.0;
    gl_Position = u_ViewProjection * model * vec4(Pos, 1.0);
    out_TexCoord = vec2(0.0, 1.0);
    EmitVertex();

    Pos.y -= 1.0;
    Pos += right;
    gl_Position = u_ViewProjection * model * vec4(Pos, 1.0);
    out_TexCoord = vec2(1.0, 0.0);
    EmitVertex();

    Pos.y += 1.0;
    gl_Position = u_ViewProjection * model * vec4(Pos, 1.0);
    out_TexCoord = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}