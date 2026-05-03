#include <bits/stdc++.h>

struct position {
    float x;
    float y;
    float z;

    bool isNULL() {return x == -1 and y == -1 and z == -1;}
};

struct cameraAngle {
    float yaw; // Horizontal (a number from 0-360) - 0 increasing x axis
    float pitch; // Vertical (-90 [straight up] to 90 [straight down])
    position pos;

    // given X position, return the position of the intercept
    position get_X_Intercept(float x) {
        float degs_to_rads = M_PI / 180.0f;

        float tan_yaw = tan(this->yaw * degs_to_rads);
        float tan_pitch = tan(this->pitch * degs_to_rads);

        if (this->yaw != 0 or this->yaw != 180) {
            float y = tan_yaw * (x - this->pos.x) + this->pos.y;
            float z = tan_pitch * sqrt(pow(this->pos.x - this->pos.x, 2) + pow(y - this->pos.y, 2)) + this->pos.z;
            return {x, y, z};
        } else return {-1, -1, -1};
    }

    position get_Y_Intercept(float y) {
        float degs_to_rads = M_PI / 180.0f;

        float tan_yaw = tan(this->yaw * degs_to_rads);
        float tan_pitch = tan(this->pitch * degs_to_rads);

        if (this->yaw != 90 or this->yaw != 270) {
            float x = (y - this->pos.y) / tan_yaw + this->pos.x;
            float z = tan_pitch * sqrt(pow(this->pos.x - this->pos.x, 2) + pow(y - this->pos.y, 2)) + this->pos.z;
            return {x, y, z};
        } else return {-1, -1, -1};
    }
};