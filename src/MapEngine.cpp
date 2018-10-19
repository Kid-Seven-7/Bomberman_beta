/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapEngine.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:54:37 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/17 14:10:38 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/MapEngine.hpp"

MapEngine::MapEngine(){}

MapEngine::~MapEngine(){}

//gets maps from the map directory
int    MapEngine::getMapPaths(std::string mapsDir){
	int numberOfMaps = 0;
	int skipDirs = 0;
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(mapsDir.c_str())) != NULL){
		while ((ent = readdir(dir)) != NULL){
			if (skipDirs > 1){
				this->mapPaths.push_back(mapsDir + "/" + ent->d_name);
				numberOfMaps++;
			}
			skipDirs++;
		}
		closedir(dir);
	}
	else{
		std::cout << "Error: Unable to open maps folder." << std::endl;
		exit(-1);
	}

	if (numberOfMaps > 2)
	return numberOfMaps;
	else{
		std::cout << "Error: Not enough maps found." << std::endl;
		exit(-1);
	}
}

void    MapEngine::dumpCurrentMap(int mapIndex){
	std::ofstream file("gameState/mapstate.txt");
	file
		<< "Map data\n"
		<< mapIndex
		<< ":"
		<< this->maps_objects[mapIndex].size()
		<< ":"
		<< this->maps_objects[mapIndex][0].size()
		<< '\n';
  for (size_t j = 0; j < this->maps_objects[mapIndex].size(); j++){
    for (size_t k = 0; k < this->maps_objects[mapIndex][j].size(); k++)
      file << this->maps_objects[mapIndex][j][k];
		file << std::endl;
  }
}

void    MapEngine::convertMaps()
{
	std::ifstream   mapFile;
	std::stringstream   mapData;
	std::string mapLine;
	std::vector<std::vector<int> > convertedMap;
	std::vector<int> convertedMapLine;
	int width = 0; //width of the map
	int height = 0; //length of the map

	for (std::vector<std::string>::iterator x = this->mapPaths.begin(); x != this->mapPaths.end(); x++){
		mapFile.open(*x);  //opening file for reading
		mapData << mapFile.rdbuf(); //getting map data
		mapFile.close(); //closing map file

		//Getting width and height of the map
		width = this->getMapWidth(mapData);
		height = this->getMapHeight(mapData);

		//coverting map data to ints
		while (std::getline(mapData, mapLine)){
			for (std::string::iterator k = mapLine.begin(); k != mapLine.end(); k++)
				convertedMapLine.push_back(static_cast<int>(*k - '0'));
			convertedMap.push_back(convertedMapLine);
			convertedMapLine.clear();
		}

		//Adding converted map to maps_objects variable
		this->maps_objects.push_back(convertedMap);

		//clearing the map for next data
		convertedMap.clear();
		mapData.clear();
	}
}

std::vector<std::vector<std::vector<int> > > MapEngine::getObjectsMaps(){
	return this->maps_objects;
}

int     MapEngine::getMapWidth(std::stringstream &mapData){
	std::string line;
	int width = 0;

	try{
		std::getline(mapData, line);
		width = static_cast<int>(std::stoi(line));
	}catch (std::exception e){
		std::cout << e.what() << std::endl;
	}

	if (width > 3)
	return (width);
	return (-1);
}

int     MapEngine::getMapHeight(std::stringstream &mapData){
	std::string line;
	int height = 0;

	try{
		std::getline(mapData, line);
		height = static_cast<int>(std::stoi(line));
	}catch (std::exception e){
		std::cout << e.what() << std::endl;
	}

	if (height > 3)
	return (height);
	return (-1);
}

void    MapEngine::createMapFromFile(std::string mapPath){
	(void)mapPath;
}

void	MapEngine::updateCurrentMap(int	currentMap, std::vector<std::vector<int> > map)
{
	//Updating current map of objects
	this->maps_objects[currentMap].clear();
	this->maps_objects[currentMap] = map;
}
