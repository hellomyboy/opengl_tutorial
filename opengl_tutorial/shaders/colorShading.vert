#version 130

in vec2 vertexPosoiton;
in vec4 vertexColor;

out vec4 fragmentColor;

void main()
{
	gl_Position.xy = vertexPosoiton;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fragmentColor = vertexColor;
}