#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

#define DEBUG
using namespace std;

//debug
string scene_names[7] = { "../testcases/scene01_basic.txt",
        "../testcases/scene02_cube.txt",
        "../testcases/scene03_sphere.txt",
        "../testcases/scene04_axes.txt",
        "../testcases/scene05_bunny_200.txt",
        "../testcases/scene06_bunny_1k.txt",
        "../testcases/scene07_shine.txt" };
//debug

int main(int argc, char *argv[]) {
//    SceneParser* sp[7] = { NULL };
//    for (int i = 0; i < 7; ++i) {
//        sp[i] = new SceneParser(scene_names[i].c_str());
//    }
#ifndef DEBUG
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2];  // only bmp is allowed.

    // TODO: Main RayCasting Logic
    // First, parse the scene using SceneParser.
    SceneParser sp(inputFile.c_str());
#else
    SceneParser sp(scene_names[0].c_str());
#endif
    Camera* camera = sp.getCamera();
    Group* baseGroup = sp.getGroup();
    Image img(camera->getWidth(), camera->getHeight());

    // Then loop over each pixel in the image, shooting a ray
    // through that pixel and finding its intersection with
    // the scene.  Write the color at the intersection to that
    // pixel in your output image.
    for (int x = 0; x < camera->getWidth(); ++x) {
        for (int y = 0; y < camera->getHeight(); ++y) {
            Ray current = camera->generateRay(Vector2f(x, y));
            Hit hit;
            bool isIntersect = baseGroup->intersect(current, hit, 0);
            if(isIntersect){
                Vector3f finalColor = Vector3f::ZERO;
                for(int li = 0; li < sp.getNumLights(); ++li){
                    Light* light = sp.getLight(li);
                    Vector3f L, lightColor;
                    light->getIllumination(current.pointAtParameter(hit.getT()), L, lightColor);
                    finalColor += hit.getMaterial()->Shade(current, hit, L, lightColor);
                }
                img.SetPixel(x, y, finalColor);
            }
            else{
                img.SetPixel(x, y, sp.getBackgroundColor());
            }
        }
    }
    img.SaveBMP("test7.bmp");
#ifndef DEBUG
    img.SaveBMP(outputFile.c_str());
#endif
    cout << "Hello! Computer Graphics!" << endl;
    return 0;
}

