/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapEngine.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatshiy <amatshiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 16:39:50 by amatshiy          #+#    #+#             */
/*   Updated: 2018/10/17 14:10:49 by amatshiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_ENGINE
# define MAP_ENGINE

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <dirent.h>

class MapEngine
{
    public:
        MapEngine();
        ~MapEngine();

        int     getMapPaths(std::string mapsDir);
        void    convertMaps();
				void 		dumpCurrentMap(int mapIndex);
        std::vector<std::vector<std::vector<int> > > getObjectsMaps();
        void    updateCurrentMap(int currentMap, std::vector<std::vector<int> > map);

    private:
        std::vector<std::string> mapPaths;
        std::vector<std::vector<std::vector<int> > >  maps_objects;
        int     getMapWidth(std::stringstream & mapData);
        int     getMapHeight(std::stringstream & mapData);
        void    createMapFromFile(std::string mapPath);
};

# endif
