#version 400
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location=2) in vec2 vt;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 pos;
out vec3 worldPosition;
out vec3 worldNormal;
out vec2 vt_out;

void main ( void ) {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
	vec4 worldPositionVec4 = modelMatrix * vec4(vp, 1.0f);
	worldPosition = vec3(worldPositionVec4 / worldPositionVec4.w);
    worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
	vt_out = vt;
}
