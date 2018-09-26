#!usr/bin/env/bash

#         _
#        (_)___  ____ _____  ____ ___  ____ _
#       / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
#      / / / / / /_/ / /_/ / / / / / / /_/ /
#   __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
#  /___/      /____/


RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

#brew installation
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
echo "${BLUE}checking for brew...${NC}"
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
if [ ! -d $HOME/.brew ];
then
	echo ${RED}brew not found${NC}
	echo ${ORANGE}installing brew...${NC}
  sh -c "$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)";	source ~/.zshrc
else
	echo ${GREEN}brew found${NC}
fi

#glm installation
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
echo "${BLUE}checking for glm...${NC}"
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
if [ ! -d $HOME/.brew/Cellar/glm ];
then
	echo ${RED}glm not found${NC}
	echo ${ORANGE}installing glm...${NC}
  brew install glm;	source ~/.zshrc
else
	echo "${GREEN}glm found${NC}"
fi

#assimp installation
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
echo "${BLUE}checking for assimp...${NC}"
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
if [ ! -d $HOME/.brew/Cellar/assimp ];
then
	echo ${RED}assimp not found${NC}
	echo ${ORANGE}installing assimp...${NC}
  brew install assimp;	source ~/.zshrc
else
	echo "${GREEN}assimp found${NC}"
fi

#update module installation
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
echo "${BLUE}checking for submodules...${NC}"
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
if [ -z "$(ls -A SFML)" ];
then
	echo ${RED}submodules not found${NC}
	echo ${ORANGE}cloning submodules...${NC}
	git submodule update --init --recursive
else
	echo ${GREEN}submodules found${NC}
	echo ${ORANGE}updating submodules...${NC}
	git submodule foreach git pull origin master
fi

#unzip assets
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
echo "${BLUE}unzipping assets...${NC}"
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
if [ -z "$(ls -A bomberman_assets)" ];
then
	echo ${RED}bomberman_assets not found${NC}
else
	echo ${GREEN}bomberman_assets found${NC}
	cd bomberman_assets
	sh unzip.sh
	cd sounds2 && mv * ../sounds
	rm sounds2
	cd ..
fi

#SFML Frameworks check
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
echo "${BLUE}checking for sfml frameworks...${NC}"
printf ${CYAN}'%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -${NC}
if [ ! -d ~/Library/frameworks ];
then
	echo ${RED}no frameworks folder found${NC}
	echo ${ORANGE}creating frameworks directory...${NC}
  mkdir /Library/Frameworks
else
	echo "${GREEN}Frameworks directory found${NC}"
fi

if [ ! -d ~/Library/frameworks/FLAC.framework ];
then
	echo ${RED}no FLAC.framework folder found${NC}
	echo ${ORANGE}copying FLAC.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/FLAC.framework ~/Library/Frameworks
else
	echo "${GREEN}FLAC.framework directory found${NC}"
fi

if [ ! -d ~/Library/frameworks/freetype.framework ];
then
	echo ${RED}no freetype.framework folder found${NC}
	echo ${ORANGE}copying freetype.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/freetype.framework ~/Library/Frameworks
else
	echo "${GREEN}freetype.framework directory found${NC}"
fi

if [ ! -d ~/Library/frameworks/ogg.framework ];
then
	echo ${RED}no ogg.framework folder found${NC}
	echo ${ORANGE}copying ogg.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/ogg.framework ~/Library/Frameworks
else
	echo "${GREEN}ogg.framework directory found${NC}"
fi

if [ ! -d ~/Library/frameworks/OpenAL.framework ];
then
	echo ${RED}no OpenAL.framework folder found${NC}
	echo ${ORANGE}copying OpenAL.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/OpenAL.framework ~/Library/Frameworks
else
	echo "${GREEN}OpenAL.framework directory found"
fi

if [ ! -d ~/Library/frameworks/vorbis.framework ];
then
	echo ${RED}no vorbis.framework folder found${NC}
	echo ${ORANGE}copying vorbis.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/vorbis.framework ~/Library/Frameworks
else
	echo ${GREEN}vorbis.framework directory found${NC}
fi

if [ ! -d ~/Library/frameworks/vorbisfile.framework ];
then
	echo ${RED}no vorbisfile.framework folder found${NC}
	echo ${ORANGE}copying vorbisfile.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/vorbisfile.framework ~/Library/Frameworks
else
	echo "${GREEN}vorbisfile.framework directory found"
fi

if [ ! -d ~/Library/frameworks/vorbisenc.framework ];
then
	echo ${RED}no vorbisenc.framework folder found${NC}
	echo ${ORANGE}copying vorbisenc.framework directory...${NC}
  cp -rf LIB_1/SFML/extlibs/vorbisenc.framework ~/Library/Frameworks
else
	echo ${GREEN}vorbisenc.framework directory found${NC}
fi

if [ ! -d ~/Library/frameworks/sfml-audio.framework ];
then
	echo ${RED}no sfml-audio.framework folder found${NC}
	echo ${ORANGE}copying sfml-audio.framework directory...${NC}
  cp -rf LIB_1/SFML/Frameworks/sfml-audio.framework ~/Library/Frameworks
else
	echo "${GREEN}FLAC.framework directory found${NC}"
fi

clear

echo ${GREEN}Bomberman and all dependencies successfully installed and setup${NC}
