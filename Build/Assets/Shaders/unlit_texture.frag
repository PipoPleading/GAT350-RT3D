#version 430

//in layout(location = 0) vec3 color;
in layout(location = 1) vec2 texcoord;

out layout(location = 0) vec4 ocolor;

uniform vec4 color;
uniform vec2 offset;
uniform vec2 tiling;

layout(binding = 0)uniform sampler2D tex;// possible to have multiple for multiple textureSamples

void main()
{
	vec4 texcolor = texture(tex, (texcoord * tiling) + offset);
	//if(texcolor.a <0.8f) discard;
	ocolor = texcolor * color;
}