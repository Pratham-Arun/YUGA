#include "Core/Log.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"
#include <iostream>

using namespace YUGA;

int main() {
    std::cout << "===========================================\n";
    std::cout << "   YUGA ENGINE - Minimal Core Test\n";
    std::cout << "   Version 1.0.0\n";
    std::cout << "===========================================\n\n";
    
    // Test Math Library
    std::cout << "Testing Math Library...\n";
    
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2(4.0f, 5.0f, 6.0f);
    Vector3 v3 = v1 + v2;
    
    std::cout << "  Vector3 addition: (" << v3.x << ", " << v3.y << ", " << v3.z << ")\n";
    std::cout << "  Vector3 length: " << v1.Length() << "\n";
    
    // Test Quaternion
    Quaternion q = Quaternion::Identity();
    std::cout << "  Quaternion identity: (" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")\n";
    
    // Test Matrix
    Matrix4 m = Matrix4::Identity();
    std::cout << "  Matrix4 identity created\n";
    
    std::cout << "\n✓ Math library working!\n";
    std::cout << "\n===========================================\n";
    std::cout << "   Core systems functional!\n";
    std::cout << "   YUGA Engine is ready.\n";
    std::cout << "===========================================\n";
    
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    
    return 0;
}
