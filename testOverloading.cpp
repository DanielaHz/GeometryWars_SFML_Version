#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <fstream>

int main()
{
    std::ofstream out("dani.txt");
    Vec2 v1(1.0f, 2.0f);
    Vec2 v2(3.0f, 4.0f);

    // Test operator overloads
    Vec2 v3 = v1 + v2;
    Vec2 v4 = v1 - v2;
    Vec2 v5 = v1 * 2.0f;
    Vec2 v6 = v2 / 2.0f;

    // Test equality and inequality
    bool isEqual = (v1 == v2);
    bool isNotEqual = (v1 != v2);

    // Test compound assignment operators
    v1 += v2;
    v2 -= v1;
    v3 *= 3.0f;
    v4 /= 2.0f;

    // Test distance and length functions
    float distance = v1.dist(v2);
    float v1Length = v1.length();
    float v2Length = v2.length();

    // Display the results
    out << "v1: (" << v1.x << ", " << v1.y << ")"
        << "\n";
    out << "v2: (" << v2.x << ", " << v2.y << ")"
        << "\n";
    out << "v3: (" << v3.x << ", " << v3.y << ")"
        << "\n";
    out << "v4: (" << v4.x << ", " << v4.y << ")"
        << "\n";
    out << "v5: (" << v5.x << ", " << v5.y << ")"
        << "\n";
    out << "v6: (" << v6.x << ", " << v6.y << ")"
        << "\n";

    out << "v1 == v2: " << isEqual << "\n";
    out << "v1 != v2: " << isNotEqual << "\n";

    out << "Distance between v1 and v2: " << distance << "\n";
    out << "Length of v1: " << v1Length << "\n";
    out << "Length of v2: " << v2Length << "\n";

    out << "Length of v2: " << v1.x << "\n";
    out.close();

    // Game g("config.txt");
    // g.run();
    return 0;
}
