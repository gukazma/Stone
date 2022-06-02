#version 460 core
layout (location = 0) in float  in_Type; 
layout (location = 1) in vec3   in_Position; 

layout (location = 0) out float     out_Type; 
layout (location = 1) out vec3      out_Position; 

void main()
{
    out_Position = in_Position;
    out_Type = in_Type;
}