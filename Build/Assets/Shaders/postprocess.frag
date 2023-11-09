#version 430

in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

layout(binding = 0)uniform sampler2D screenTexture;

void main()
{
	vec4 texcolor = texture(screenTexture, ftexcoord);
	ocolor = texcolor;
}