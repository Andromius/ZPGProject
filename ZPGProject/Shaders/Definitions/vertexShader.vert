#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 pos;
out vec3 worldPosition;
out vec3 worldNormal;

void main ( void ) {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
	vec4 worldPositionVec4 = modelMatrix * vec4(vp, 1.0f);
	worldPosition = vec3(worldPositionVec4);
    worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
}
