#version 330 core
in vec4 m_color;
in vec2 uv;
out vec4 FragColor;
void main()
{
	FragColor = m_color;
}