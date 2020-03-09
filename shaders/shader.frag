#version 330 core

in float sampleExtraOutput;

uniform vec3 color;

out vec4 fragColor;

void main()
{
    // Use the color passed in. An alpha of 1.0f means it is not transparent.
    fragColor = vec4(color, sampleExtraOutput);
}