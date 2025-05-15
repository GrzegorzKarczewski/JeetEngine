#pragma once
#include <glad/glad.h>

class Mesh {
public:
    Mesh(float *vertices, size_t vertexSize, unsigned int* indices, size_t indexCount);
    ~Mesh();
    void Draw();

private:
    unsigned int VAO, VBO, EBO;
    size_t m_indexCount;
};
