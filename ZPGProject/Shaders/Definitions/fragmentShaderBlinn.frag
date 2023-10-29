﻿#version 400
in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 objectColor;
uniform float specularStrength;
uniform int shininess;
uniform float lightAttenuation;

void main ( void ) 
{
	vec3 cameraDirection = normalize(cameraPosition - worldPosition);
	vec3 lightDirection = normalize(lightPosition - worldPosition);  

	vec3 halfwayDirection = normalize(lightDirection + cameraDirection);
	
	float spec = pow(max(dot(worldNormal, halfwayDirection), 0.0), shininess);

	vec4 specularColor = specularStrength * spec * lightColor;
	
	float diff = max(dot(lightDirection, worldNormal), 0.0);
	
	vec4 diffuseColor = diff * lightColor;
	vec4 ambientColor = vec4( 0.1, 0.1, 0.1, 1.0);
	
	float distance = length(lightPosition - worldPosition);
	float attenuation = 1.0 / (1.0 + lightAttenuation * distance * distance);

	gl_FragColor = (ambientColor + attenuation * (diffuseColor + specularColor)) * objectColor;
}