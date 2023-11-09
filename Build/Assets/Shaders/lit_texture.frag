#version 430

#define POINT 0
#define DIRECTIONAL 1
#define SPOT 2

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
	int type;
	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;
	float range;
	float innerAngle;
	float outerAngle;

} light;

vec3 ads(in vec3 position, in vec3 normal)
{
	// AMBIENT
	vec3 ambient = ambientLight;

	// ATTENUATION

	float attenuation = 1;
	if (light.type != DIRECTIONAL)
	{
		float distanceSqr = dot(light.position - position, light.position - position);
		float rangeSqr = pow(light.range, 2.0); // to the power of 2
		attenuation = pow(max(0, 1 - pow(( distanceSqr / rangeSqr ), 2.0)), 2.0);

	}

	// DIFFUSE
	//doing diffuse here after the vert cal
	vec3 lightDir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(light.color - position); //head - tail = direction, dot products need to be normalized for cos
	
	float spotIntensity = 1;
	if(light.type == SPOT)
	{
		float angle = acos(dot(light.direction, lightDir));
		//if (angle > light.innerAngle) spotIntensity = 0;
		spotIntensity = smoothstep(light.outerAngle, light.innerAngle, angle);
	}

	float intensity = max(dot(lightDir, normal), 0) * spotIntensity;
	vec3 diffuse = material.diffuse * (light.color * intensity);

	// SPECULAR
	vec3 specular = vec3(0);
	if (intensity > 0)

	{
		vec3 reflection = reflect(-light.color, normal);
		vec3 viewDir = normalize(-position); //non normalized allows for some cool stuff, i need to experiment with it
		intensity = max(dot(reflection, viewDir), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * intensity * spotIntensity  * light.intensity;

	}

	return ambient + (diffuse + specular) * light.intensity * attenuation;
}

void main()
{
	vec4 texcolor = texture(tex, ftexcoord);
	ocolor = (texcolor * vec4(ads(fposition, fnormal), 1));
//can add flat vec4 to the front to force flat shading within color rather than phong
}