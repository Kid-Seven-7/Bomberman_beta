/*
       _
      (_)___  ____ _____  ____ ___  ____ _
     / / __ \/ __ `/ __ \/ __ `__ \/ __ `/
    / / / / / /_/ / /_/ / / / / / / /_/ /
 __/ /_/ /_/\__, /\____/_/ /_/ /_/\__,_/
/___/      /____/
*/

# include "../include/bomberman.hpp"

float convertValue(std::string line, int val){
  int demarks = 1;
  std::string temp;

  for (size_t i = 0; i < line.length(); ++i){
    if (line[i] == ':'){
      demarks++;
      i++;
    }
    if (demarks == val)
      temp += line[i];
  }

  return (std::stod(temp,NULL));
}
