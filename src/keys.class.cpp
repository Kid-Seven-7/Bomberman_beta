/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/keys.hpp"
# include <iostream>
# include <unistd.h>

Keys::~Sound(){}

Keys::Sound()
:_up(265), _down(264), _left(263), _right(262)
{

}

void Keys::setKeys(std::string type){
	if (type == "numpad"){
		this->_up = 328;
		this->_down = 322;
		this->_left = 324;
		this->_right = 326;
	}else if (type == "wasd"){
		this->_up = 87;
		this->_down =083 ;
		this->_left = 65;
		this->_right = 68;
	}else{
		this->_up = 265;
		this->_down = 264;
		this->_left = 263;
		this->_right = 262;
	}
}

int Keys::input(){

}
