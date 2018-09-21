/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/sound.hpp"
# include <iostream>
# include <unistd.h>

//Foreward declerations
void LoadSound(sf::Music &buffer, std::string filepath);
void playSFX(sf::Music &buffer);
void setSound(sf::Music &buffer, sf::Music &buffer1, sf::Music &buffer2);

Sound::~Sound(){}

Sound::Sound()
:_loop(1)
{
	//Initiates all sounds used in the game
	LoadSound(this->_loop1, "bomberman_assets/sounds/loop1.wav");
	LoadSound(this->_loop2, "bomberman_assets/sounds/loop2.wav");
	LoadSound(this->_loop3, "bomberman_assets/sounds/loop3.wav");
	LoadSound(this->_loop4, "bomberman_assets/sounds/loop4.wav");
	LoadSound(this->_loop5, "bomberman_assets/sounds/loop5.wav");
	LoadSound(this->_loop6, "bomberman_assets/sounds/loop6.wav");
	LoadSound(this->_loop7, "bomberman_assets/sounds/loop7.wav");
	LoadSound(this->_loop8, "bomberman_assets/sounds/loop8.wav");
	LoadSound(this->_loop9, "bomberman_assets/sounds/loop9.wav");
	LoadSound(this->_ghost, "bomberman_assets/sounds/ghost.wav");
	LoadSound(this->_swipe, "bomberman_assets/sounds/swipe.wav");
	LoadSound(this->_bomb, "bomberman_assets/sounds/blast.wav");
}

/* Plays a SFX based on the value passed in */
void Sound::playFX(int sound){
	switch (sound){
		case GHOST:
			playSFX(this->_ghost);
			break;
		case SWIPE:
			playSFX(this->_swipe);
			break;
		case BLAST:
			playSFX(this->_bomb);
			break;
	}
}

/* returns the value of _loop (the loop currently playing) */
int Sound::getLoopValue() const{
return (this->_loop);
}

/* plays the next loop */
void Sound::nextLoop(){
	this->_loop++;
	playloop();
}

/* Plays the previous loop */
void Sound::prevLoop(){
	if(this->_loop > 1){
		this->_loop--;
		playloop();
	}
}

/* Chooses which loop to play based on the value of _loop */
void Sound::playloop(){
	switch (this->_loop) {
		case 1:
			setSound(this->_loop1, this->_loop2, this->_loop9);
			break;
		case 2:
			setSound(this->_loop2, this->_loop1, this->_loop3);
			break;
		case 3:
			setSound(this->_loop3, this->_loop2, this->_loop4);
			break;
		case 4:
			setSound(this->_loop4, this->_loop3, this->_loop5);
			break;
		case 5:
			setSound(this->_loop5, this->_loop4, this->_loop6);
			break;
		case 6:
			setSound(this->_loop6, this->_loop5, this->_loop7);
			break;
		case 7:
			setSound(this->_loop7, this->_loop6, this->_loop8);
			break;
		case 8:
			setSound(this->_loop8, this->_loop7, this->_loop9);
			break;
		case 9:
			setSound(this->_loop9, this->_loop8, this->_loop1);
			break;
		default:
			setSound(this->_loop1, this->_loop1, this->_loop9);
			break;
	}
}

/* Loads sound into the buffer */
void Sound::LoadSound(sf::Music &buffer, std::string filepath){
	if(!buffer.openFromFile(filepath))
	std::cout
		<< RED
		<< "error: \n"
		<< "Could not open "
		<< filepath
		<< '\n';
}

/* Ensures that a sound has been stopped before playing it */
void playSFX(sf::Music &buffer){
	buffer.stop();
	buffer.play();
}

/* Plays the current loop ensuring that all other loops have been stopped */
void setSound(sf::Music &buffer, sf::Music &buffer1, sf::Music &buffer2){
	buffer.stop();
	buffer1.stop();
	buffer2.stop();
	buffer.setLoop(true);
	buffer.play();
}

void Sound::setVolumeLevel(std::string type, float level){
	if (type == "LOOP"){
		this->_loop1.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop2.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop3.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop4.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop5.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop6.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop7.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop8.setVolume(this->getVolumeLevel("LOOP") + level);
		this->_loop9.setVolume(this->getVolumeLevel("LOOP") + level);
	}
	if (type == "SFX"){
		this->_bomb.setVolume(this->getVolumeLevel("SFX") + level);
		this->_swipe.setVolume(this->getVolumeLevel("SFX") + level);
		this->_ghost.setVolume(this->getVolumeLevel("SFX") + level);
		this->_oneup.setVolume(this->getVolumeLevel("SFX") + level);
		this->_death.setVolume(this->getVolumeLevel("SFX") + level);
	}
	else
		return;
}

float Sound::getVolumeLevel(std::string type){
	if (type == "LOOP")
		return(this->_loop1.getVolume());
	if (type == "SFX")
		return(this->_bomb.getVolume());
	else
		return (-1.0f);
}
