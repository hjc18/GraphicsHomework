#include "mesh.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <sstream>
bool Mesh::AABBTest(const Ray &r, const Hit &h, double tmin) {
    Vector3f o = r.getOrigin();
    if(o[0] <= AABB[0] && o[0] >= AABB[1]
    && o[1] <= AABB[2] && o[1] >= AABB[3]
    && o[2] <= AABB[4] && o[2] >= AABB[5]) return true; //inside the box
    double tttmax = (AABB[0] - o[0]) / r.getDirection()[0];
    double tttmin = (AABB[1] - o[0]) / r.getDirection()[0];
    if(tttmax < tttmin) swap(tttmax, tttmin);
    double ttmax = tttmax;
    double ttmin = tttmin;
    tttmax = (AABB[2] - o[1]) / r.getDirection()[1];
    tttmin = (AABB[3] - o[1]) / r.getDirection()[1];
    if(tttmax < tttmin) swap(tttmax, tttmin);
    ttmax = min(ttmax, tttmax);
    ttmin = max(ttmin, tttmin);
    tttmax = (AABB[4] - o[2]) / r.getDirection()[2];
    tttmin = (AABB[5] - o[2]) / r.getDirection()[2];
    if(tttmax < tttmin) swap(tttmax, tttmin);
    ttmax = min(ttmax, tttmax);
    ttmin = max(ttmin, tttmin);
    return ttmax >= ttmin;
}
bool Mesh::intersect(const Ray &r, Hit &h, double tmin) {
    // Optional: Change this brute force method into a faster one.
    bool result = false;
    if(!AABBTest(r, h, tmin)) return false;
    for (int triId = 0; triId < (int) t.size(); ++triId) {
        TriangleIndex& triIndex = t[triId];
        Triangle triangle(v[triIndex[0]],
                          v[triIndex[1]], v[triIndex[2]], material);
        triangle.normal = n[triId];
        result |= triangle.intersect(r, h, tmin);
    }
    return result;
}

Mesh::Mesh(const char *filename, Material *material) : Object3D(material) {
    // Optional: Use tiny obj loader to replace this simple one.
    std::ifstream f;
    f.open(filename);
    if (!f.is_open()) {
        std::cout << "Cannot open " << filename << "\n";
        return;
    }
    std::string line;
    std::string vTok("v");
    std::string fTok("f");
    std::string texTok("vt");
    char bslash = '/', space = ' ';
    std::string tok;
    int texID;
    while (true) {
        std::getline(f, line);
        if (f.eof()) {
            break;
        }
        if (line.size() < 3) {
            continue;
        }
        if (line.at(0) == '#') {
            continue;
        }
        std::stringstream ss(line);
        ss >> tok;
        if (tok == vTok) {
            Vector3f vec;
            ss >> vec[0] >> vec[1] >> vec[2];
            if(v.empty()){
                AABB[0] = AABB[1] = vec[0];
                AABB[2] = AABB[3] = vec[1];
                AABB[4] = AABB[5] = vec[2];
            }
            else {
                if (vec[0] > AABB[0]) AABB[0] = vec[0];
                else if (vec[0] < AABB[1]) AABB[1] = vec[0];
                if (vec[1] > AABB[2]) AABB[2] = vec[1];
                else if (vec[1] < AABB[3]) AABB[3] = vec[1];
                if (vec[2] > AABB[4]) AABB[4] = vec[2];
                else if (vec[2] < AABB[5]) AABB[5] = vec[2];
            }
            v.push_back(vec);
        } else if (tok == fTok) {
            if (line.find(bslash) != std::string::npos) {
                std::replace(line.begin(), line.end(), bslash, space);
                std::stringstream facess(line);
                TriangleIndex trig;
                facess >> tok;
                for (int ii = 0; ii < 3; ii++) {
                    facess >> trig[ii] >> texID;
                    trig[ii]--;
                }
                t.push_back(trig);
            } else {
                TriangleIndex trig;
                for (int ii = 0; ii < 3; ii++) {
                    ss >> trig[ii];
                    trig[ii]--;
                }
                t.push_back(trig);
            }
        } else if (tok == texTok) {
            Vector2f texcoord;
            ss >> texcoord[0];
            ss >> texcoord[1];
        }
    }
    computeNormal();
    f.close();
}

void Mesh::computeNormal() {
    n.resize(t.size());
    for (int triId = 0; triId < (int) t.size(); ++triId) {
        TriangleIndex& triIndex = t[triId];
        Vector3f a = v[triIndex[1]] - v[triIndex[0]];
        Vector3f b = v[triIndex[2]] - v[triIndex[0]];
        b = Vector3f::cross(a, b);
        n[triId] = b / b.length();
    }
}
