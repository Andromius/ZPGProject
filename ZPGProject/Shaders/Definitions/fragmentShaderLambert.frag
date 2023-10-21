#version 330
in vec3 worldPosition;
in vec3 worldNormal;
uniform vec3 lightPosition;
uniform vec4 lightColor;

void main( void ){
    vec3 lightDirection = normalize(lightPosition - worldPosition);
    float dotProduct = max(dot(lightDirection, worldNormal), 0.0);
    
    vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);
    vec4 diffuseColor = dotProduct * lightColor;
    vec4 ambientColor = vec4( 0.1, 0.1, 0.1, 1.0);
    gl_FragColor = ( ambientColor + diffuseColor ) * objectColor;
}
