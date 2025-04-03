#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <fstream>


#include "forme.h"
#include "camera.h"

//fonction d enregistrement en ppm
void save_ppm(const std::string& filename, const std::vector<Objet*>& objets, int width, int height);







#endif