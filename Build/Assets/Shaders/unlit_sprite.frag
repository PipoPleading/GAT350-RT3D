#version 430

in layout(location = 0) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;



uniform struct Material
{
	vec3 albedo;
	
	vec2 offset;
	vec2 tiling;
	//potential offset & tiling location
} material;

layout(binding = 0)uniform sampler2D tex;// possible to have multiple for multiple textureSamples

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);

	if(texcolor.a < 0.5) discard; //cuts out invisible pixels for the purpose of the z buffer
	ocolor = texcolor * vec4(material.albedo, 1);
}