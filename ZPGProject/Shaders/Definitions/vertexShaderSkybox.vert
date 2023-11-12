#version 400
layout(location=0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

out vec3 fragmentLocalPosition;

void main()
{
	mat4 tl = mat4(1);
	tl[3].x = cameraPosition.x;
	tl[3].y = cameraPosition.y;
	tl[3].z = cameraPosition.z;
	gl_Position = projectionMatrix * viewMatrix * tl * vec4(vp, 1.0f);
	fragmentLocalPosition = vp;
}
