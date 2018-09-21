//         _
//        (_)___  ____ _____  ____ ___  ____ _
//       / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
//      / / / / / /_/ / /_/ / / / / / / /_/ /
//	 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
//	/___/      /____/

#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
}
