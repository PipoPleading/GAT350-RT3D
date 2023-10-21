#version 430

//vertex data
in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;

//outdata for frag
out layout(location = 0) vec3 oposition;
out layout(location = 1) vec3 onormal;
out layout(location = 2) vec2 otexcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform struct Adjust //transforms for the material
{
vec2 offset;
vec2 tiling;

} adjust;

void main()
{

	mat4 modelView = view * model;

	// convert position and normal to world-view space
	oposition = vec3(modelView  * vec4(vposition, 1));
	onormal = normalize(mat3(modelView) * vnormal);
	otexcoord = (vtexcoord * adjust.tiling) + adjust.offset;

	//mvp to give positions for use in frag
	mat4 mvp = projection * view * model; 
	gl_Position = mvp * vec4(vposition, 1.0);
}
