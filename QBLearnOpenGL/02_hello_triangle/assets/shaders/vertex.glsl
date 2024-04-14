#version 330 core
in vec3 aPos;
out vec4 m_color;
uniform float time;
void main()
{
	 float posOffsetX = (sin(time)/2.0f);
	 float posOffsetY = sin(time / 10.0f);
	 gl_Position = vec4(aPos.x+posOffsetX, aPos.y+posOffsetY, aPos.z, 1.0f);

	 float alpha = (sin(time)+1.0f)/2.0f;
	 m_color = vec4(1.0f, 0.5f, 0.2f, 1f)* alpha;
}