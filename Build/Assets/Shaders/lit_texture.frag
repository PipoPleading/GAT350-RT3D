#version 430

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

layout(binding = 0)uniform sampler2D tex;// possible to have multiple for multiple textureSamples

uniform vec3 ambientLight; //global

uniform struct Material{
vec3 diffuse;
vec3 specular;
float shininess;
} material;

uniform struct Light // use this instead of individual variables 
{
	vec3 diffuseLight;
	vec3 lPosition;

} light;

vec3 ads(in vec3 position, in vec3 normal)
{
	// AMBIENT
	vec3 ambient = ambientLight;

	// DIFFUSE
	//doing diffuse here after the vert cal
	vec3 lightDir = normalize(light.lPosition - position); //head - tail = direction, dot products need to be normalized for cos
	float intensity = max(dot(lightDir, normal), 0);
	vec3 diffuse = material.diffuse * (light.diffuseLight * intensity);

	// SPECULAR
	vec3 specular = vec3(0);
	if (intensity > 0)

	{
		vec3 reflection = reflect(-light.lPosition, normal);
		vec3 viewDir = normalize(-position); //non normalized allows for some cool stuff, i need to experiment with it
		intensity = max(dot(reflection, viewDir), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * intensity;

	}

	return ambient + diffuse + specular;
}

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);
	ocolor = (texcolor * vec4(ads(fposition, fnormal), 1));
//can add flat vec4 to the front to force flat shading within color rather than phong
}