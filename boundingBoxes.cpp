#include <bits/stdc++.h>
#include "cameraAngle.cpp"

using namespace std;

struct boundingBox {
    float x, y, z;
    float length_x, length_y, length_z;

    float getMaxX() {return x + length_x;}
    float getMaxY() {return y + length_y;}
    float getMaxZ() {return z + length_z;}

    bool checkBoundingBoxIntercept(cameraAngle ray) {
        // check X min
        float degs_to_rads = M_PI / 180.0f;

        float tan_yaw = tan(ray.yaw * degs_to_rads);
        float tan_pitch = tan(ray.pitch * degs_to_rads);

        // checks min_x_intercpt
        if (ray.yaw != 0 and ray.yaw != 180) {
            auto intercept = ray.get_X_Intercept(this->x);
            if (intercept.y >= this->y and intercept.y <= this->getMaxY() and 
                intercept.z >= this->z and intercept.z <= this->getMaxZ()) 
                    return true;

            intercept = ray.get_X_Intercept(this->getMaxX());
            if (intercept.y >= this->y and intercept.y <= this->getMaxY() and 
                intercept.z >= this->z and intercept.z <= this->getMaxZ()) 
                    return true;
        }

        // checks y intercepts
        if (ray.yaw != 90 and ray.yaw != 270) {
            auto intercept = ray.get_Y_Intercept(this->y);
            if (intercept.y >= this->y and intercept.y <= this->getMaxY() and 
                intercept.z >= this->z and intercept.z <= this->getMaxZ()) 
                    return true;

            intercept = ray.get_Y_Intercept(this->getMaxY());
            if (intercept.x >= this->x and intercept.x <= this->getMaxX() and 
                intercept.z >= this->z and intercept.z <= this->getMaxZ()) 
                    return true;
        }

        // checks z intercepts
        if (ray.pitch != 90 or ray.pitch != -90) {
            auto intercept = ray.get_Z_Intercept(this->z);
            if (intercept.y >= this->y and intercept.y <= this->getMaxY() and 
                intercept.z >= this->z and intercept.z <= this->getMaxZ()) 
                    return true;

            intercept = ray.get_Z_Intercept(this->getMaxZ());
            if (intercept.x >= this->x and intercept.x <= this->getMaxX() and 
                intercept.y >= this->y and intercept.y <= this->getMaxY()) 
                    return true;
        }

        return false;
    }
};