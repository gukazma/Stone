#version 460 core
layout(points) in;
layout(points, max_vertices = 1) out;

layout (location = 0) in float[] geoValue; 
layout (location = 0) out float outValue;


void main()
{
    outValue = geoValue[0] + 1;
    EmitVertex();

    EndPrimitive();
}