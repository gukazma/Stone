#version 460 core
layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

layout (location = 0) in float[] geoValue; 
layout (location = 0) out float outValue;


void main()
{
	for (int i = 0; i < 3; i++) {
        outValue = geoValue[0] + i;
        EmitVertex();
    }

    EndPrimitive();
}