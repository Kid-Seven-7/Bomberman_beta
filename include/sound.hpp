/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# ifndef 			SOUND_HPP
# define 			SOUND_HPP

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
// # define 			LOOP1 16
// # define 			LOOP2 17
// # define 			LOOP3 18
// # define 			LOOP4 19
// # define 			LOOP5 20
// # define 			LOOP6 21
// # define 			LOOP7 22
// # define 			LOOP8 23
// # define 			LOOP9 24

// # include "bomberman.hpp"
# include 		<SFML/Audio.hpp>

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

		//SFX
		sf::Music _bomb;
		sf::Music _swipe;
		sf::Music _ghost;
		sf::Music _oneup;
		sf::Music _death;

	public:
		Sound();
		~Sound();

		void 			nextLoop();
		void 			prevLoop();
		void 			playloop();
		void 			playFX(int sound);
		void 			LoadSound(sf::Music &buffer, std::string filepath);
		int 			getLoopValue() const;
		void 			setVolumeLevel(std::string type, float level);
		float 		getVolumeLevel(std::string type);
};

#endif
