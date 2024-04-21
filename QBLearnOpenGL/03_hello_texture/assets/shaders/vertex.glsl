#version 330 core
in vec3 aPos;
out vec4 m_color;
void main()
{
	 gl_Position = vec4(aPos, 1.0f);
	 m_color = vec4(1.0f, 0.5f, 0.2f, 1f);
}