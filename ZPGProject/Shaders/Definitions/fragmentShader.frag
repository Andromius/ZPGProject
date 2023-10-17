#version 330
out vec4 frag_colour;
in vec3 pos;
void main () {
     frag_colour = vec4(pos, 1.0);
}
