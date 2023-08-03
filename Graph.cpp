#include "Graph.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <AAGL/Graphics.h>
#include <AAGL/Mesh.h>
#include <AAGL/Shape.h>
#include "Helper.h"

Graph:: Graph(Graphics* graphics, float x, float y, float w, float h) :graphics(graphics), x(x), y(y), w(w), h(h) {
    mesh = new Mesh("graph");
    graphShape = new Shape(graphics, mesh);
    graphShape->drawType = GL_LINE_STRIP;
    graphShape->col = glm::vec4(1., 1., 1., 1.);
    recalculateView();
}

Graph::~Graph() {
    delete mesh;
    delete graphShape;
}

void Graph::addData(std::vector<float> &data) {
    mesh->build(data);
}

void Graph::render(glm::mat4 projection) {
    if(mesh->built) {
        graphShape->render(projection);   
    }
}

void Graph::setDimensions(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    recalculateView();
}

float Graph::getX() {
    return x;
}

float Graph::getY() {
    return y;
}

float Graph::getW() {
    return w;
}

float Graph::getH() {
    return h;
}

void Graph::recalculateView() {
    graphShape->view = Helper::quadMat(w/2. + x, h/2. + y, w/2., h/2.);
}