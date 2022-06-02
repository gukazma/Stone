#version 460 core
layout (location = 0) in float  in_Type; 
layout (location = 1) in vec3   in_Position; 
layout (location = 2) in vec3   in_Velocity; 
layout (location = 3) in float  in_Age; 

layout (location = 0) out float     out_Type; 
layout (location = 1) out vec3      out_Position; 
layout (location = 2) out vec3      out_Velocity; 
layout (location = 3) out float     out_Age; 

void main()
{
    out_Type        = in_Type;
    out_Position    = in_Position;
    out_Velocity    = in_Velocity;
    out_Age         = in_Age;
}