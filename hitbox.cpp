#include <bits/stdc++.h>
using namespace std;
#include "position.cpp"

struct hitbox {
    // IsHit, depth
    virtual pair<bool,int> checkCollision();
    virtual int getDensity();
};

struct pillHitbox : hitbox {
    position p1;
    position p2;
};