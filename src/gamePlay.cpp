/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/HeaderHandler.hpp"
# include "../include/bomberman.hpp"

void gameplay(GLFWwindow *window, Sound &sound, Keys &keys){
	GraphicsEngine *g_engine = new GraphicsEngine(window);
	g_engine->MainControl(sound, keys);
	delete  g_engine;
}
