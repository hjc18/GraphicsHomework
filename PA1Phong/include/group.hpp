#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>


// TODO: Implement Group - add data structure to store a list of Object*
class Group : public Object3D {

public:

    Group() = delete;

    explicit Group (int num_objects):size(num_objects){
        objList.resize(num_objects);
    }

    ~Group() override {
        for(auto e : objList){
            if(e) delete e;
        }
    }

    bool intersect(const Ray &r, Hit &h, double tmin) override {
        bool isIntersect = false;
        for (int i = 0; i < size; ++i) {
            isIntersect |= objList[i]->intersect(r, h, tmin);
        }
        return isIntersect;
    }

    void addObject(int index, Object3D *obj) {
        objList[index] = obj;
    }

    int getGroupSize() {
        return size;
    }

private:
    std::vector<Object3D*> objList;
    int size;
};

#endif
	
