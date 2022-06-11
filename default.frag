#version 330 core

in vec3 fColor;
in vec2 fTexCoord;

out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
   FragColor = vec4(fColor,0);// + 0.0 * texture(tex0, fTexCoord);
}