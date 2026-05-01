#include <bits/stdc++.h>
using namespace std;

// Determines the max coords of the map to avoid unnecessary computations.
int max_coords = 1e4;
int min_coords = 0;

int bound_size = 1e2;

struct object {
    // Some filler for how objects are stored
};

struct position {
    float x;
    float y;
    float z;
};

// The unique ranges for yaw and pitch are to avoid division by 0 problems
position getNextBox(float yaw, float pitch, position pos) {
    float x_hypot_length = INT_MAX;
    if (yaw < 90 or yaw > 270) {
        x_hypot_length = ((pos.x / bound_size) + 1) * bound_size / sin(yaw * M_PI / 180.0f);
    } else if (yaw < 90 or yaw > 270) {
        x_hypot_length = ((pos.x / bound_size)) * bound_size / sin(yaw * M_PI / 180.0f);
    }

    float y_hypot_length = INT_MAX;
    if (yaw < 180) {
        y_hypot_length = ((pos.y / bound_size) + 1) * bound_size / cos(yaw * M_PI / 180.0f);
    } else if (yaw > 180) {
        y_hypot_length = ((pos.y / bound_size)) * bound_size / cos(yaw * M_PI / 180.0f);
    }

    float z_hypot_length = INT_MAX;
    if (pitch > 0) {
        z_hypot_length = ((pos.z / bound_size) + 1) * bound_size / sin(pitch * M_PI / 180.0f);
    } else if (pitch < 0) {
        z_hypot_length = ((pos.z / bound_size)) * bound_size / sin(pitch * M_PI / 180.0f);
    }

    float hypot_length = x_hypot_length;
    hypot_length = max(hypot_length, y_hypot_length);
    hypot_length = max(hypot_length, z_hypot_length);

    position res;

    if (x_hypot_length >= y_hypot_length and x_hypot_length >= z_hypot_length) {
        res.x = ceil(pos.x + sin(yaw * M_PI / 180.0f) * x_hypot_length);
        res.y = (pos.y + cos(yaw * M_PI / 180.0f) * x_hypot_length);
        res.z = (pos.z + sin(pitch * M_PI / 180.0f) * x_hypot_length);
    } else if (y_hypot_length >= x_hypot_length and y_hypot_length >= z_hypot_length) {
        res.x = (pos.x + sin(yaw * M_PI / 180.0f) * y_hypot_length);
        res.y = ceil(pos.y + cos(yaw * M_PI / 180.0f) * y_hypot_length);
        res.z = (pos.z + sin(pitch * M_PI / 180.0f) * y_hypot_length);
    } else {
        res.x = (pos.x + sin(yaw * M_PI / 180.0f) * z_hypot_length);
        res.y = (pos.y + cos(yaw * M_PI / 180.0f) * z_hypot_length);
        res.z = ceil(pos.z + sin(pitch * M_PI / 180.0f) * z_hypot_length);
    }
    
    return res;
}

bool checkContinuePath(position pos) {
    if (pos.x >= max_coords or pos.y >= max_coords or pos.z >= max_coords) return false;
    else if (pos.x <= 0 or pos.y <= 0 or pos.z <= 0) return false;
    else return true;
}

struct cameraAngle {
    float yaw; // Horizontal (a number from 0-360) 0 is forward with rotation clockwise
    float pitch; // Vertical (-90 [straight up] to 90 [straight down])
    position pos;

    vector<object> checkCollisions() {
        auto cur_pos = this->pos;
        while(checkContinuePath(cur_pos)) {
            // Check entities in partition;
            cur_pos = getNextBox(yaw, pitch, pos);
        }
    }
};