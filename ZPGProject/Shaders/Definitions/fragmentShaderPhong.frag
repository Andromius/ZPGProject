# version 400
in vec3 worldPosition;
in vec3 worldNormal;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;

void main ( void )
{
	float specularStrength = 1;
	vec3 cameraDirection = normalize(cameraPosition - worldPosition);
    vec3 lightDirection = normalize(lightPosition - worldPosition);
	
	vec3 reflectDirection = reflect(-lightDirection , worldNormal);
	float spec = pow(max(dot(cameraDirection, reflectDirection), 0.0), 32);
	vec4 specularColor = specularStrength * spec * lightColor;
	
	float dotProduct = max(dot(lightDirection, worldNormal), 0.0);
	
	vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);
	vec4 diffuseColor = dotProduct * lightColor;
    vec4 ambientColor = vec4( 0.1, 0.1, 0.1, 1.0);
	gl_FragColor = (ambientColor + diffuseColor + specularColor) * objectColor;
}