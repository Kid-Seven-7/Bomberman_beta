/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GraphicsEngine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:28:24 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/19 12:11:52 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GRAPHICS_ENGINE
# define GRAPHICS_ENGINE

# include "HeaderHandler.hpp"
# include "bomberman.hpp"
# include "BombClass.hpp"
# include "Enemy.hpp"
# include <cmath>
# include <unistd.h>
# include <limits>

//Global Variables
#define WIDTH 1200
#define HEIGHT 800

void    framebuffer_size_callback(GLFWwindow *window, int width, int height);
bool    processInput(Keys &keys);

//Collision detection variables
static  float   nextXPos = 2.6f;
static  float   nextYPos = 2.6f;
static  float   prevXpos = -2.6f;
static  float   prevYpos = -2.6f;

//Graphics Objects
# define    FLOOR   0
# define    HARD_WALL   1
# define    SOFT_WALL   2
# define    PLAYER_OBJ  3
# define    BOMB    4
# define    ENEMY   5
# define    DOOR    6

// ENEMY DIRECTION GLOBALS
# define    ENEMY_UP 1
# define    ENEMY_DOWN 2
# define    ENEMY_RIGHT 3
# define    ENEMY_LEFT 4

class GraphicsEngine
{
    public:
        GraphicsEngine();
		GraphicsEngine(GLFWwindow  *window);
        ~GraphicsEngine();

        void    glfwConfig();
        void    gladConfg();
        void    MainControl(Sound &sound, Keys &keys);
        void    RestartGame(Sound &sound, Keys &keys, GLFWwindow  *window);
        void    callMovementFunctions(Player &player, Sound &sound, Keys &keys, std::vector<std::vector<int> > mapOfObjects);
        void    shaderConfig();
        void    modelProjectionConfig();
        void    updateMap(Player player, std::vector<std::vector<int> > & map);
        std::vector<std::vector<int> >  getCurrentObjectsMap();
        bool    ft_deleteEnemy(int x_pos, int y_pos, std::vector<std::vector<int> > & map);

        //Variable for enemy objects
        std::vector<Enemy>  enemies;
        bool    restart_game;

    private:
        GLFWwindow  *window;
        CameraClass cam;
        Shader  ourShader;

        //Positions of objects
        double   pos_x;
        double   pos_y;

        //Current Map
        int     currentMap;

        //Current Player Direction
        int player_direction;

        //Player lives
        int lives;

        //Enemy vector from map
        std::vector<std::vector<int> >    enemyNumbers;
        int     bombXCoord;
        int     bombYCoord;

        //Remove player life from banch
        void    remove_life(std::vector<std::vector<int> > & map);
        void    reset_player_location(std::vector<std::vector<int> > & map);

        //Reset camera position
        void    reset_camera();


        //Array check for Bomb placement
        bool    array_check(std::vector<std::vector<int> > & map);
        void    remove_bomb(std::vector<std::vector<int> > & map);
        bool    createEnemyArray(std::vector<std::vector<int> >  map, unsigned int numCheck = 1);
        int     update_bomb_range(std::vector<std::vector<int> > & map);

        //ENEMY DELETION
        bool                deleteEnemy;
        unsigned int        currentEnemy;
        int                 currentDeletedEnemy;
        bool                skipMapUpdate;
        std::vector<std::vector<float> > enemyCoords;
};

# endif
