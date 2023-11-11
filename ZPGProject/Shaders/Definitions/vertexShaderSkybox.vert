#version 400
layout(location=0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;

out vec3 fragmentLocalPosition;

void main()
{
	mat4 tl = mat4(1);
	tl[3].x = cameraPos.x;
	tl[3].y = cameraPos.y;
	tl[3].z = cameraPos.z;
	gl_Position = tl * vec4(vp, 1.0f);
	fragmentLocalPosition = vp;
}
