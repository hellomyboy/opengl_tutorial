#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 outColor;

uniform float time;
uniform sampler2D mySampler;

void main() 
{
	vec4 uvColor = texture(mySampler, fragmentUV);
	//outColor = uvColor;

	/* outColor = fragmentColor + vec4((sin(time) + 1) * 0.5, 
					(sin(time + 2) + 1) * 0.5,
					(cos(time + 3) + 1) * 0.5,
					1.0) * uvColor;  */

	outColor = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4 + time) + 1) * 0.5,
					fragmentColor.g * (cos(fragmentPosition.y * 8 + time) + 1) * 0.5,
					fragmentColor.b * (cos(fragmentPosition.x * 4 + time) + 1) * 0.5, fragmentColor.a) * uvColor;
	
}