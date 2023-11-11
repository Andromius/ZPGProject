#version 400

in vec2 vt_out;

uniform int samplingConstant;
uniform sampler2D textureUnitID;

void main () {
    gl_FragColor = texture(textureUnitID, vt_out * samplingConstant);
    //gl_FragColor = vec4(vt_out, 0, 1);
}