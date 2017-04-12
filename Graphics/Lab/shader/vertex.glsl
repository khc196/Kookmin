#version 120    // GLSL 1.2  (OpenGL 2.x)

uniform mat4 u_M;
uniform mat4 u_V; // View Matrix
uniform mat4 u_P;

// W 는 OpenGL에서 자동으로 해준다. Shader에서 해주진 않는다.

attribute vec4 a_position;
attribute vec4 a_color;
varying vec4 v_color;


void main()
{
  v_color = a_color;
  gl_Position = u_P * u_V * u_M * a_position; // 슬라이드에선 u_V : V의 역행렬
}
