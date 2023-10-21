#version 430

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;
in layout(location = 3) vec4 fcolor; //can add flat to the front to force flat shading rather than per pixel/vertex

out layout(location = 0) vec4 ocolor;

layout(binding = 0)uniform sampler2D tex;// possible to have multiple for multiple textureSamples

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);
	ocolor = texcolor * fcolor;
}