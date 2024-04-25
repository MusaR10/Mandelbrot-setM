#include "ComplexPlane.h"
#include <complex>
#include <cmath>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight){
	m_pixel_size = {pixelWidth, pixelHeight};
	m_aspectRatio = (float)pixelHeight / (float)pixelWidth;
	m_plane_center = {0, 0};
	m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
	m_ZoomCount = 0;
	m_state = State::CALCULATING
	m_vArray = setPrimitiveType(Points);
	m_vArray.resize(pixelWidth*pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const{
    target.draw(m_vArray);
}

/*update render
void ComplexPlane::updateRender(){
if m_state == State::CALCULATING{
	for int i/i<y
 		for int j/ j<x
   		m_vArray[...]
     		Vector2f position = mapPTC(j,i);
       		int iteration = countiterations(position);
	 	iterate to r,g,b
   		add color to vArray
        state::Displaying
}
}
*/
void ComplexPlane::zoomIn(){
    m_ZoomCount++;
    float x_size = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    float y_size = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
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

void ComplexPlane::loadText(Text& text){
    stringstream ss;
    ss<< "Mandelbrot set\n";
    ss<< "Center: " << m_plane_center.x << ", " << m_plane_center.y << "\n";
    ss<< "Size: " << m_plane_size.x << ", " << m_plane_size.y<< "\n";
    ss<< "Left click to zoom in\n";
    ss<< "Right click to zoom out\n";
    text.setString(ss.str());
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    text.setPosition(10,10);
}

int ComplexPlane::countIterations(Vector2f coord){
    size_t iterations = 0;
    complex<double> x (0,0);
    complex<double> c (coord.x, coord.y);
    while(iterations < MAX_ITER && abs(x)<2){
        x=pow(x,2)+c;
        iterations++;
    }
    return iterations;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b){
	if(count == MAX_ITER){
        	r = 0;
        	g = 0;
        	b = 0;
    	}
	else if (count<10){
		r=192;
		g=0;
		b=255;
	}
	else if (count<20){
		r=0;
		g=255;
		b=0;
	}
	else if (count<30){
		r=0;
		g=175;
		b=12;
	}
	else if (count<40){
		r=0;
		g=0;
		b=255;
	}

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel){
  float x = ((mousePixel.x-0)/ static_cast<float>(m_pixelWidth))* m_plane_size.x + (m_plane_center.x-m_plane_size.x/ 2.0);
  float y = ((mousePixel.y-m_pixelHeight)/ static_cast<float>(0-m_pixelHeight))* m_plane_size.y + (m_plane_center.y-m_plane_size.y/ 2.0);
  return {x,y};
}
