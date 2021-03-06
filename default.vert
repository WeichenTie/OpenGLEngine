#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 fColor;
out vec2 fTexCoord;

uniform float uScale;

void main()
{
   gl_Position = vec4(aPos.x * uScale, aPos.y * uScale, aPos.z * uScale, 1.0);
   fColor = aColor;
   fTexCoord = aTexCoord;
}