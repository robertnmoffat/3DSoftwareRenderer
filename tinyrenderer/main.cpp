#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {

	int xDiff = x1 - x0, yDiff = y1-y0;
	int length = sqrt(xDiff*xDiff+yDiff*yDiff);
	float its = 1. / (float)length;

	for (float t = 0.; t < 1; t+=its) {
		int x = round(x0*(1. - t) + x1*t);
		int y = round(y0*(1. - t) + y1*t);
		image.set(x,y,color);
	}
}

void drawRandomLines(int amount, TGAImage image) {
	for (int i = 0; i < amount; i++) {
		line(rand() % 100, rand() % 100, rand() % 100, rand() % 100, image, white);
	}
}

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	//image.set(52, 41, red);

	drawRandomLines(10, image);	

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	
	return 0;
}