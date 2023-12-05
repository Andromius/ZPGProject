#version 400


in vec2 vt_out;


uniform sampler2D textureUnitID;

void main ()
{
    gl_FragColor = texture(textureUnitID, vt_out);
}