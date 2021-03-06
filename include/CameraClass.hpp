/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraClass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 09:28:57 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/17 12:13:17 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# ifndef CAMERA_CLASS
# define CAMERA_CLASS

# include "shader.hpp"
# include "model.hpp"
# include "keys.hpp"
# include <GLFW/glfw3.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class CameraClass
{
    public:
        CameraClass();
        ~CameraClass();

        void    setCam(Shader shader);
        void    camMovements(Keys &keys);
        void    camRotation(GLFWwindow *window);
        void    playerCamMovements(Keys &keys);
		void    saveinfo();

        //Camera Configs
        glm::vec3   cameraPos;
        glm::vec3   cameraFront;
        glm::vec3   cameraUp;

    private:
        //Camera Speed
        float       camSpeed;
        float       playerCamSpeed;

        //Camera Movement variables
        float       rotate_cam_x;
        float       rotate_cam_y;
};

# endif
