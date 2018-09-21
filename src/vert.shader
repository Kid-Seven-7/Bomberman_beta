//         _
//        (_)___  ____ _____  ____ ___  ____ _
//       / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
//      / / / / / /_/ / /_/ / / / / / / /_/ /
//	 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
//	/___/      /____/

#version 410 core
	layout (location = 0) in vec3 aPos;

	uniform vec4 newPosition;

	void main(){
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		gl_Position.xyzw += vec4(newPosition.x, newPosition.y, newPosition.z, 0.0);
	}
