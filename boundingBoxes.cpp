#include <bits/stdc++.h>
#include "cameraAngle.cpp"

using namespace std;

struct boundingBox {
    float x, y, z;
    float length_x, length_y, length_z;

    float getMaxX() {return x + length_x;}
    float getMaxY() {return y + length_y;}
    float getMaxZ() {return z + length_z;}
};

pair<bool, int> checkBoundingBoxIntercept(cameraAngle ray, boundingBox target) {
    pair<bool,int> hitAndLength = {false, 0};

    // For each edge check where the line intercepts.

    set<position> interceptPoints;

    // check X min
    float degs_to_rads = M_PI / 180.0f;

    float tan_yaw = tan(ray.yaw * degs_to_rads);
    float tan_pitch = tan(ray.pitch * degs_to_rads);

    // checks min_x_intercpt
    if (ray.yaw != 0 and ray.yaw != 180) {
        auto intercept = ray.get_X_Intercept(target.x);
        if (intercept.y >= target.y and intercept.y <= target.getMaxY() and 
            intercept.z >= target.z and intercept.z <= target.getMaxZ()) 
                interceptPoints.insert(intercept);

        intercept = ray.get_X_Intercept(target.getMaxX());
        if (intercept.y >= target.y and intercept.y <= target.getMaxY() and 
            intercept.z >= target.z and intercept.z <= target.getMaxZ()) 
                interceptPoints.insert(intercept);
    }

    // checks y intercepts
    if (ray.yaw != 90 and ray.yaw != 270) {
        auto intercept = ray.get_Y_Intercept(target.y);
        if (intercept.y >= target.y and intercept.y <= target.getMaxY() and 
            intercept.z >= target.z and intercept.z <= target.getMaxZ()) 
                interceptPoints.insert(intercept);

        intercept = ray.get_Y_Intercept(target.getMaxY());
        if (intercept.x >= target.x and intercept.x <= target.getMaxX() and 
            intercept.z >= target.z and intercept.z <= target.getMaxZ()) 
                interceptPoints.insert(intercept);
    }

    // checks z intercepts
    if (ray.pitch != 90 or ray.pitch != -90) {
        auto intercept = ray.get_Z_Intercept(target.z);
        if (intercept.y >= target.y and intercept.y <= target.getMaxY() and 
            intercept.z >= target.z and intercept.z <= target.getMaxZ()) 
                interceptPoints.insert(intercept);

        intercept = ray.get_Z_Intercept(target.getMaxZ());
        if (intercept.x >= target.x and intercept.x <= target.getMaxX() and 
            intercept.y >= target.y and intercept.y <= target.getMaxY()) 
                interceptPoints.insert(intercept);
    }





}