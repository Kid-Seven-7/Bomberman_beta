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
void playSFX(sf::Music &buffer);
void setSound(sf::Music &buffer, sf::Music &buffer1, sf::Music &buffer2);

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Sound deconstructor
*/
Sound::~Sound(){}

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Sound constructor
*/
Sound::Sound()
:_loop(1)
{
	//Initiates all sounds used in the game
	LoadSound(this->_ost1, "bomberman_assets/sounds/On the Precipice of Defeat.wav");
	LoadSound(this->_loop1, "bomberman_assets/sounds/Devil Eyes.wav");
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
	LoadSound(this->_bomb, "bomberman_assets/sounds/drop.wav");
	LoadSound(this->_fucked, "bomberman_assets/sounds/fucked.wav");
	LoadSound(this->_bassdrop, "bomberman_assets/sounds/BombBlast.wav");
	LoadSound(this->_bb8_death, "bomberman_assets/sounds/bb8_death.wav");
	LoadSound(this->_bb8_sound, "bomberman_assets/sounds/bb8_sound.wav");
	LoadSound(this->_bb8_sound1, "bomberman_assets/sounds/bb8_sound1.wav");
	LoadSound(this->_bb8_sound2, "bomberman_assets/sounds/bb8_sound2.wav");
	LoadSound(this->_bb8_sound3, "bomberman_assets/sounds/bb8_sound3.wav");
	LoadSound(this->_bb8_sound4, "bomberman_assets/sounds/bb8_sound4.wav");
	LoadSound(this->_bb8_sound5, "bomberman_assets/sounds/bb8_sound5.wav");
}

/*
	Parameters:
		int sound- A MACRO defining which sound to play
	Return:
		void
	Synopsis:
		Plays a sound based on the value passed in
*/
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
		case BASS:
			playSFX(this->_bassdrop);
			break;
		case BB8_DEATH:
			playSFX(this->_bb8_death);
			break;
		case FUCKED:
			playSFX(this->_fucked);
			break;
		case BB8_MISC:
			srand (time(NULL));
			int randomNumber = (rand() % 6 + 1);
			if (randomNumber == 1)
				playSFX(this->_bb8_sound);
			else if (randomNumber == 2)
				playSFX(this->_bb8_sound1);
			else if (randomNumber == 3)
				playSFX(this->_bb8_sound2);
			else if (randomNumber == 4)
				playSFX(this->_bb8_sound3);
			else if (randomNumber == 5)
				playSFX(this->_bb8_sound4);
			else if (randomNumber == 6)
				playSFX(this->_bb8_sound5);
			break;
	}
}

/*
	Parameters:
		int sound- A MACRO defining which sound to play
	Return:
		void
	Synopsis:
		Plays a sound based on the value passed in
*/
void Sound::playOST(int sound){
	switch (sound){
		case PRECIPICE:
			playSFX(this->_ost1);
			break;
		case SWIPE:
			playSFX(this->_swipe);
			break;
		case BLAST:
			playSFX(this->_bomb);
			break;
		case BASS:
			playSFX(this->_bassdrop);
			break;
	}
}

/*
	Parameters:
		void
	Return:
		int- Active loop
	Synopsis:
		Returns the value of active loop
*/
int Sound::getLoopValue() const{
return (this->_loop);
}

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Incrementes the value of the current loop
		playing the next loop
*/
void Sound::nextLoop(){
	this->_loop++;
	playloop();
}

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Decrementes the value of the current loop
		playing the previous loop
*/
void Sound::prevLoop(){
	if(this->_loop > 1){
		this->_loop--;
		playloop();
	}
}

/*
	Parameters:
		void
	Return:
		void
	Synopsis:
		Plays the current loop and pauses the niebouring loops
*/
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

/*
	Parameters:
		sf::Music &buffer- Buffer to load sound into
		std::string filepath- Path to the sound file to load
	Return:
		void
	Synopsis:
		Loads sound into buffer.
		Prints error message on failure
*/
void Sound::LoadSound(sf::Music &buffer, std::string filepath){
	if(!buffer.openFromFile(filepath))
	std::cout
		<< RED
		<< "error: \n"
		<< "Could not open "
		<< filepath
		<< '\n';
}

/*
	Parameters:
		std::string type- Sound type
		float level- Sound level
	Return:
		void
	Synopsis:
		Sets the volume level of various sounds
*/
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
		this->_ost1.setVolume(this->getVolumeLevel("LOOP") + level);
	}
	if (type == "SFX"){
		this->_bomb.setVolume(this->getVolumeLevel("SFX") + level);
		this->_swipe.setVolume(this->getVolumeLevel("SFX") + level);
		this->_ghost.setVolume(this->getVolumeLevel("SFX") + level);
		this->_oneup.setVolume(this->getVolumeLevel("SFX") + level);
		this->_death.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bassdrop.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_death.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_sound.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_sound1.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_sound2.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_sound3.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_sound4.setVolume(this->getVolumeLevel("SFX") + level);
		this->_bb8_sound5.setVolume(this->getVolumeLevel("SFX") + level);
	}
	else
		return;
}

/*
	Parameters:
		std::string type- Sound type
	Return:
		float- Current sound level of the defined sound type,
			or -1.0f on failure
	Synopsis:
		Returns the sound level of the defined sound type
*/
float Sound::getVolumeLevel(std::string type){
	if (type == "LOOP")
		return(this->_loop1.getVolume());
	if (type == "SFX")
		return(this->_bomb.getVolume());
	else
		return (-1.0f);
}

/*
Parameters:
	sf::Music &buffer- Sound buffer
Return:
	void
Synopsis:
	Plays the sound buffer passed in
*/
void playSFX(sf::Music &buffer){
	buffer.stop();
	buffer.play();
}

/*
Parameters:
	sf::Music &buffer- Current sound buffer
	sf::Music &buffer1- Neibouring sound buffer
	sf::Music &buffer2- Neibouring sound buffer
Return:
	void
Synopsis:
	Plays current sound buffer in a loop and stops the neibouring sound buffers
*/
void setSound(sf::Music &buffer, sf::Music &buffer1, sf::Music &buffer2){
	buffer.stop();
	buffer1.stop();
	buffer2.stop();
	buffer.setLoop(true);
	buffer.play();
}
