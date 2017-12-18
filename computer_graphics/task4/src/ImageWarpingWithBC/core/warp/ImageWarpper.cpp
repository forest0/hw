#include "ImageWarpper.h"

ImageWarpper::ImageWarpper() 
    :image(nullptr), vertices()
{

}

ImageWarpper::ImageWarpper(QImage * image, 
        std::vector<QPoint >vertices)
    :image(image), vertices(vertices)
{

}

void ImageWarpper::warp(int index, const QPoint & delta) {

}

ImageWarpper::~ImageWarpper() {

}

void ImageWarpper::setImage(QImage * image) {
    this->image = image;
}

void ImageWarpper::setVertices(std::vector<QPoint >vertices) {
    this->vertices = vertices;
}

void ImageWarpper::init() {

}

