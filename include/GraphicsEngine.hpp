/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:28:24 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 15:49:26 by amatshiy         ###   ########.fr       */
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

class GraphicsEngine
{
    public:
        GraphicsEngine();
				GraphicsEngine(GLFWwindow  *window);
        ~GraphicsEngine();

        void    glfwConfig();
        void    gladConfg();
        void    MainControl(Sound &sound, Keys &keys);
        void    callMovementFunctions(Player &player, Sound &sound, Keys &keys);
        void    shaderConfig();
        void    modelProjectionConfig();
        std::vector<std::vector<std::vector<float>>> getCoordsMap();
        std::vector<std::vector<int>>  getCurrentObjectsMap();

    private:
        GLFWwindow  *window;
        CameraClass cam;
        Shader  ourShader;

        //Positions of objects
        float   pos_x;
        float   pos_y;

        //Vector of Coordinates
        std::vector<float>  xy_coords;
        std::vector<std::vector<float>> array_of_xy;
        std::vector<std::vector<std::vector<float>>>  map_of_coords; // Map of object coordinates

        //Current Map
        int     currentMap;
        void    dumpArray();
};

# endif
