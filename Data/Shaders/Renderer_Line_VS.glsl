in vec3 a_Pos;
in vec4 a_Color;

uniform UBO
{
  mat4 ProjectionViewMatrix;
} u_Data;

out vec4 Color;

void main()
{
  gl_Position = u_Data.ProjectionViewMatrix * vec4(a_Pos, 1.0);

  Color = a_Color;
}
