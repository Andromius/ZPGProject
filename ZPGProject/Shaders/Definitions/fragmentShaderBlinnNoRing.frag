#version 400
#define MAX_LIGHTS 10

#define LIGHT_POINT 0
#define LIGHT_DIRECTIONAL 1
#define LIGHT_SPOT 2

in vec3 worldPosition;
in vec3 worldNormal;
in vec2 vt_out;

uniform vec3 cameraPosition;
uniform vec4 objectColor;
uniform float specularStrength;
uniform int shininess;
uniform int hasTexture;
uniform vec4 ambientColorFactor;

uniform int samplingConstant;
uniform sampler2D textureUnitID;

uniform int numberOfLights;

struct light
{
	vec3 position;
	vec4 color;
	float attenuationQuadratic;
	float attenuationLinear;
	float diffuseStrength;
	vec3 direction;
	int type;
	float angle;
	float angleFadeStart;
};

uniform light lights[MAX_LIGHTS];

void main ( void )
{
	vec3 cameraDirection = normalize(cameraPosition - worldPosition);
    
	for (int i = 0; i < numberOfLights; i++)
	{
		int lightType = lights[i].type;
		vec3 lightDirection;
		
		if(lightType == LIGHT_DIRECTIONAL) 
			lightDirection = lights[i].direction;
		else 
			lightDirection = normalize(lights[i].position - worldPosition);

		vec3 halfwayDirection = normalize(lightDirection + cameraDirection);

		float spec = pow(max(dot(halfwayDirection, worldNormal), 0.0), shininess);
		
		vec4 specularColor = vec4(0);
		if(dot(worldNormal, lightDirection) >= 0)
		{
			specularColor = specularStrength * spec * lights[i].color;
		}
		
		float diff = max(dot(lightDirection, worldNormal), 0.0);
		
		vec4 diffuseColor;
		vec4 ambientColor;
		if (hasTexture != 1)
		{
			diffuseColor = lights[i].diffuseStrength * diff * ((lights[i].color + objectColor)/2);
			ambientColor = ambientColorFactor * objectColor;
		}
		else
		{
			diffuseColor = lights[i].diffuseStrength * diff * ((lights[i].color + texture(textureUnitID, vt_out * samplingConstant))/2);
			ambientColor = ambientColorFactor * texture(textureUnitID, vt_out * samplingConstant );
		}
		
		float attenuation = 1;
		if (lightType != LIGHT_DIRECTIONAL)
		{
			float distance = length(lights[i].position - worldPosition);
			attenuation = 1.0 / (1.0 + lights[i].attenuationLinear * distance + lights[i].attenuationQuadratic * distance * distance);
		}

		if (lightType == LIGHT_SPOT) 
		{
			float spotCosine = dot(normalize(-lights[i].direction), lightDirection);
			float cosLightAngle = cos(radians(lights[i].angle));
			if (spotCosine > cosLightAngle)
			{        
				float intensity = (spotCosine - cosLightAngle) / (cos(radians(lights[i].angleFadeStart)) - cosLightAngle);
				intensity = clamp(intensity, 0.0, 1.0); 
				gl_FragColor += attenuation * intensity * (diffuseColor + specularColor);
			}
		} 
		else gl_FragColor += attenuation * (diffuseColor + specularColor);
		
		gl_FragColor += ambientColor;
	}
}
