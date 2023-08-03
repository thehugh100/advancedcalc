#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Mesh;
class Shape;
class Graphics;

class Graph {
public:
    Graph(Graphics* graphics, float x, float y, float w, float h);
    ~Graph();
    void addData(std::vector<float> &data);
    void render(glm::mat4 projection);
    void setDimensions(float x, float y, float w, float h);
    float getX();
    float getY();
    float getW();
    float getH();
private:
    void recalculateView();
    
    Mesh* mesh;
    Shape* graphShape;
    Graphics* graphics;
    float x;
    float y;
    float w;
    float h;
};