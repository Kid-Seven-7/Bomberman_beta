//         _
//        (_)___  ____ _____  ____ ___  ____ _
//       / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
//      / / / / / /_/ / /_/ / / / / / / /_/ /
//	 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
//	/___/      /____/

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
