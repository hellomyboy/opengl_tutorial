#version 130

in vec4 fragmentColor;
out vec4 outColor;

uniform float time;

void main() 
{
	outColor = fragmentColor + vec4((sin(time) + 1) * 0.5, 
					(sin(time + 2) + 1) * 0.5,
					(cos(time + 3) + 1) * 0.5,
					1.0);
}