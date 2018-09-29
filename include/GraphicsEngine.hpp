/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:28:24 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/29 16:23:03 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GRAPHICS_ENGINE
# define GRAPHICS_ENGINE

# include "HeaderHandler.hpp"
# include "bomberman.hpp"

//Global Variables
#define WIDTH 1200
#define HEIGHT 800

void    framebuffer_size_callback(GLFWwindow *window, int width, int height);
bool    processInput(Keys &keys);
static  float   nextXPos = 2.6f;
static  float   nextYPos = 2.6f;
static  float   prevXpos = -2.6f;
static  float   prevYpos = -2.6f;

class GraphicsEngine
{
    public:
        GraphicsEngine();
		GraphicsEngine(GLFWwindow  *window);
        ~GraphicsEngine();

        void    glfwConfig();
        void    gladConfg();
        void    MainControl(Sound &sound, Keys &keys);
        void    callMovementFunctions(Player &player, Sound &sound, Keys &keys, std::vector<std::vector<int> > mapOfObjects);
        void    shaderConfig();
        void    modelProjectionConfig();
        std::vector<std::vector<int>>  getCurrentObjectsMap();

    private:
        GLFWwindow  *window;
        CameraClass cam;
        Shader  ourShader;

        //Positions of objects
        float   pos_x;
        float   pos_y;

        //Current Map
        int     currentMap;
        void    dumpArray();
};

# endif
