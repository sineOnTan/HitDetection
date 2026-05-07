#include "cameraAngle.cpp"
#include "entity.cpp"
using namespace std;
#define space << " "

// Determines the max coords of the map to avoid unnecessary computations.
int max_coords = 1e4;
int min_coords = 0;

int bound_size = 1e2;

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

    float hypot_length = min(abs(x_hypot_length), abs(y_hypot_length));
    position res;

    if (abs(x_hypot_length) == hypot_length) {
        res.x = round(pos.x + cos_yaw * hypot_length);
        res.y = (pos.y + sin_yaw * hypot_length);
        res.z = (pos.z + sin_pitch * hypot_length);
    } else {
        res.x = (pos.x + cos_yaw * hypot_length);
        res.y = round(pos.y + sin_yaw * hypot_length);
        res.z = (pos.z + sin_pitch * hypot_length);
    }

    return res;
}

// Checks the next line is in the plane
bool checkContinuePath(position pos) {
    if (pos.x >= max_coords or pos.y >= max_coords or pos.z >= max_coords) return false;
    else if (pos.x <= 0 or pos.y <= 0 or pos.z <= 0) return false;
    else return true;
}

// ##########################
// small test that can be run
// ##########################
//
// int main () {
//     position pos;
//     pos.x = 10;
//     pos.y = 12;
//     pos.z = 50;
//     float pitch = 20;
//     float yaw = 45;
//     auto start = std::chrono::high_resolution_clock::now();
//     pos = getNextBox(yaw, pitch, pos);
//     // cout << pos.x space << pos.y space << pos.z << endl;

//     pos = getNextBox(yaw,pitch,pos);
//     // cout << pos.x space << pos.y space << pos.z << endl;

//     auto finish = std::chrono::high_resolution_clock::now();
//     cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() << endl;

//     return 0;
// }