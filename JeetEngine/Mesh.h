#pragma once
#include <glad/glad.h>

class Mesh {
public:
    Mesh();
    ~Mesh();
    void Draw();

private:
    unsigned int VAO, VBO, EBO;
};
