#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
    m_pixel_size = {pixelWidth, pixelHeight};
    m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_ZoomCount = 0;
    m_state = State::CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
    m_vArray.create(); 
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const{
    target.draw(m_vArray);
}

//update render

void ComplexPlane::zoomIn(){
    m_ZoomCount++;
    float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
    float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);
    m_plane_size = {x_size, y_size};
    m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut(){
  m_ZoomCount--;
  float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
  float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);
  m_plane_size = {x_size, y_size};
  m_state = State::CALCULATING;
}

