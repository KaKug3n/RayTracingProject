#include "main.h"

void save_ppm(const std::string& filename, const std::vector<Objet*>& objets, int width, int height) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << "255 255 255 "; // White pixel
        }
        file << "\n";
    }

    file.close();
}


int main(int argc, char const *argv[])
{
    int width = 80;
    int height = 60;
    std::string filename = "output.ppm";
    std::vector<Objet*> objets;

    // Test add a carre to the scene and a camera
    carre c1(point(0,0,0), point(1,0,0), point(1,1,0), point(0,1,0), materiel(1,0,0,1));
    camera cam(point(0,0,0), point(1,0,0), point(1,1,0), point(0,1,0), materiel(1,1,1,1), width, height);



    c1.print();
    cam.print();
    //
    return 0;
}
