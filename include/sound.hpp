/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# ifndef 			__SOUND_HPP__
# define 			__SOUND_HPP__

# include 		<SFML/Audio.hpp>

//Color out puts
# define 			RED "\033[0;31m"
# define 			GREEN "\033[0;32m"
# define 			ORANGE "\033[0;33m"
# define 			BLUE "\033[0;34m"
# define 			CYAN "\033[0;36m"
# define 			NC "\033[0m"

//Sounds
# define 			BLAST 10
# define 			SWIPE 11
# define 			FOOTSTEP 12
# define 			DEATH 13
# define 			ONEUP 14
# define 			GHOST 15
# define 			BASS 16
# define 			BB8_DEATH 17
# define 			BB8_MISC 18
# define 			FUCKED 19
# define 			PRECIPICE 99
// # define 			BASS
// # define 			BASS
// # define 			BASS
// # define 			BASS
// # define 			BASS

class Sound{
	private:
		int 			_loop;

		//loops
		sf::Music _loop1;
		sf::Music _loop2;
		sf::Music _loop3;
		sf::Music _loop4;
		sf::Music _loop5;
		sf::Music _loop6;
		sf::Music _loop7;
		sf::Music _loop8;
		sf::Music _loop9;

		//OST
		sf::Music _ost1;

		//SFX
		sf::Music _bomb;
		sf::Music _swipe;
		sf::Music _ghost;
		sf::Music _oneup;
		sf::Music _death;
		sf::Music _fucked;
		sf::Music _bassdrop;
		sf::Music _bb8_death;
		sf::Music _bb8_sound;
		sf::Music _bb8_sound1;
		sf::Music _bb8_sound2;
		sf::Music _bb8_sound3;
		sf::Music _bb8_sound4;
		sf::Music _bb8_sound5;

	public:
		Sound();
		~Sound();

		void 			nextLoop();
		void 			prevLoop();
		void 			playloop();
		void 			playFX(int sound);
		void 			playOST(int sound);
		void 			setVolumeLevel(std::string type, float level);
		void 			LoadSound(sf::Music &buffer, std::string filepath);
		int 			getLoopValue() const;
		float 		getVolumeLevel(std::string type);
};

# endif
