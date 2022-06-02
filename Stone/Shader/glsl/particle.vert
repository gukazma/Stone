#version 460 core
layout (location = 0) in vec3 in_Position; 

layout (location = 0) out vec3 out_Position; 

void main()
{
    out_Position = in_Position;
}