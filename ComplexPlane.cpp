#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
    m_pixel_size = {pixelWidth, pixelHeight};
    m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_zoomCount = 0;
    m_State = State::CALCULATING;
    m_vertexArray.setPrimitiveType(Points);
    m_vertexArray.resize(pixelWidth * pixelHeight);
    m_vertexArray.create(); 
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const{
    target.draw(m_vArray);
}

//update render

void ComplexPlane::zoomIn(){
    m_zoomCount++;
    float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = {x_size, y_size};
    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut(){
  m_zoomCount--;
  float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
  float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
  m_plane_size = {x_size, y_size};
  m_State = State::CALCULATING;
}

