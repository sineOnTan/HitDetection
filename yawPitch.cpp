struct position {
    int x;
    int y;
    int z;
};

struct cameraAngle {
    float yaw; // Horizontal (a number from 0-360)
    float pitch; // Vertical (-90 [straight up] to 90 [straight down])
    position pos;
};