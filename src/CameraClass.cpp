/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraClass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@42.FR>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 09:29:46 by amatshiy          #+#    #+#             */
/*   Updated: 2018/09/25 08:36:43 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/CameraClass.hpp"

CameraClass::CameraClass(){
    //setting the camera position, and angle view
    this->cameraPos = glm::vec3(0.0f, 0.0f, 18.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    //Camera movement variables init
    this->rotate_cam_x = 0.59f;
    this->rotate_cam_y = 0.0f;
}

CameraClass::~CameraClass(){}

void    CameraClass::setCam(Shader shader){
    //Setting view
    glm::mat4   view = glm::mat4(1.0f);

    view = glm::lookAt(this->cameraPos, cameraPos + cameraFront, cameraUp);
    view = glm::rotate(view, this->rotate_cam_x, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, this->rotate_cam_y, glm::vec3(0.0f, 1.0f, 0.0f));

    //Getting uniform location
    unsigned viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void    CameraClass::camMovements(Keys &keys){
	(void)keys;
    this->camSpeed = 0.5f;

    // //Updating the camera point of view
    // if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    //     this->cameraPos += this->camSpeed * this->cameraFront;
    // if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    //     this->cameraPos -= this->camSpeed * this->cameraFront;
    // if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    //     this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->camSpeed;
    // if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    //     this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->camSpeed;
    // if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    //    this->cameraPos += glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f))) * this->camSpeed;
}

void   CameraClass::camRotation(GLFWwindow *window){
    //rotate x
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        this->rotate_cam_x += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        this->rotate_cam_x -= 0.05f;
    //rotate z
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        this->rotate_cam_y += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        this->rotate_cam_y -= 0.05f;
}

void    CameraClass::playerCamMovements(Keys &keys){
    this->playerCamSpeed = 0.08f;

    if (keys.input() == UP)
        this->cameraPos += this->playerCamSpeed * this->cameraFront;
    else if (keys.input() == DOWN)
        this->cameraPos -= this->playerCamSpeed * this->cameraFront;
    if (keys.input() == RIGHT)
        this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * this->playerCamSpeed;
    else if (keys.input() == LEFT)
        this->cameraPos += glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f))) * this->playerCamSpeed;
}

void 	CameraClass::saveinfo(){
	std::ofstream file("gameState/camInfo.gsf");
	file
		<< "camSpeed"
		<< this->camSpeed
		<< "\nplayerCamSpeed"
		<< this->playerCamSpeed
		<< "\nrotate_cam_x"
		<< this->rotate_cam_x
		<< "\nrotate_cam_y"
		<< this->rotate_cam_y
		// << "\ncameraPos"
		// << this->cameraPos
		// << "\ncameraFront"
		// << this->cameraFront
		// << "\ncameraUp"
		// << this->cameraUp
		<< '\n';
}
