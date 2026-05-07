struct position {
    float x;
    float y;
    float z;

    bool isNULL() {return x == -1 and y == -1 and z == -1;}
    
    position (float xCoord = -1, float yCoord = -1, float zCoord = -1) {
        x = xCoord;
        y = yCoord;
        z = zCoord;
    }
};