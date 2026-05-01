#include <bits/stdc++.h>
using namespace std;
#define space << " "

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
// Aims to find the smallest hypotenuse to exit a plane defined by the bounding box then 
// calculate the position the line would leave the box.
position getNextBox(float yaw, float pitch, position pos) {
    float degs_to_rads = M_PI / 180.0f;

    float sin_yaw = sin(yaw * degs_to_rads);
    float cos_yaw = cos(yaw * degs_to_rads);
    float sin_pitch = sin(pitch * degs_to_rads);

    float x_hypot_length = INT_MAX;
    if (yaw < 90 or yaw > 270) {
        x_hypot_length = ((floor(pos.x / bound_size + 1) * bound_size) - pos.x) / cos_yaw;
    } else if (yaw > 90 and yaw < 270) {
        x_hypot_length = (pos.x - (floor(pos.x / bound_size) * bound_size)) / cos_yaw;
    }

    float y_hypot_length = INT_MAX;
    if (yaw < 180) {
        y_hypot_length = ((floor(pos.y / bound_size + 1) * bound_size) - pos.y) / sin_yaw;
    } else if (yaw > 180) {
        y_hypot_length = (pos.y - (floor(pos.y / bound_size) * bound_size)) / sin_yaw;
    }

    float z_hypot_length = INT_MAX;
    if (pitch > 0) {
        z_hypot_length = ((floor(pos.z / bound_size + 1) * bound_size) - pos.z) / sin_pitch;
    } else if (pitch < 0) {
        z_hypot_length = (pos.z - (floor(pos.z / bound_size) * bound_size)) / sin_pitch;
    }

    float hypot_length = abs(x_hypot_length);
    hypot_length = min(hypot_length, abs(y_hypot_length));
    hypot_length = min(hypot_length, abs(z_hypot_length));

    // cout << x_hypot_length space << y_hypot_length space << z_hypot_length space << hypot_length << endl;

    position res;

    if (abs(x_hypot_length) == hypot_length) {
        res.x = round(pos.x + cos_yaw * hypot_length);
        res.y = (pos.y + sin_yaw * hypot_length);
        res.z = (pos.z + sin_pitch * hypot_length);
    } else if (abs(y_hypot_length) == hypot_length) {
        res.x = (pos.x + cos_yaw * hypot_length);
        res.y = round(pos.y + sin_yaw * hypot_length);
        res.z = (pos.z + sin_pitch * hypot_length);
    } else {
        res.x = (pos.x + cos_yaw * hypot_length);
        res.y = (pos.y + sin_yaw * hypot_length);
        res.z = round(pos.z + sin_pitch * hypot_length);
    }

    // cout << res.x space << res.y space << res.z << endl;

    return res;
}

// Checks the next line is in the plane
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
        vector<object> res;
        while(checkContinuePath(cur_pos)) {
            // Check entities in partition;
            cur_pos = getNextBox(yaw, pitch, pos);
        }
        return res;
    }
};

int main () {
    position pos;
    pos.x = 10;
    pos.y = 12;
    pos.z = 50;
    float pitch = 20;
    float yaw = 45;
    auto start = std::chrono::high_resolution_clock::now();
    pos = getNextBox(yaw, pitch, pos);
    // cout << pos.x space << pos.y space << pos.z << endl;

    pos = getNextBox(yaw,pitch,pos);
    // cout << pos.x space << pos.y space << pos.z << endl;

    auto finish = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << endl;

    return 0;
}