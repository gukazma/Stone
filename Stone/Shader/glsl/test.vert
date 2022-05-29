#version 460 core
layout (location = 0) in float inValue; 

layout (location = 0) out float outValue; 

void main()
{
    outValue = sqrt(inValue);
}