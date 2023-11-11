#version 400


in vec3 fragmentLocalPosition;


uniform samplerCube textureUnitID;

void main ()
{
    gl_FragColor = texture(textureUnitID, fragmentLocalPosition);
}
