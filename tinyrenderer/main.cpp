#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
Model *model = NULL;
const int width = 800;
const int height = 800;

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

void line(Vec2i v0, Vec2i v1, TGAImage &image, TGAColor color) {

	int xDiff = v1.x - v0.x, yDiff = v1.y - v0.y;
	int length = sqrt(xDiff*xDiff + yDiff*yDiff);
	float its = 1. / (float)length;

	for (float t = 0.; t < 1; t += its) {
		int x = round(v0.x*(1. - t) + v1.x*t);
		int y = round(v0.y*(1. - t) + v1.y*t);
		image.set(x, y, color);
	}
}

void drawRandomLines(int amount, TGAImage &image) {
	for (int i = 0; i < amount; i++) {
		line(rand() % width, rand() % height, rand() % width, rand() % height, image, white);
	}
}

void drawLineModel(TGAImage &image) {
	for (int i = 0; i<model->nfaces(); i++) {
		std::vector<int> face = model->face(i);
		for (int j = 0; j<3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0.x + 1.)*width / 2.;
			int y0 = (v0.y + 1.)*height / 2.;
			int x1 = (v1.x + 1.)*width / 2.;
			int y1 = (v1.y + 1.)*height / 2.;
			line(x0, y0, x1, y1, image, white);
		}
	}
}

void drawTriangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
	line(t0, t1, image, color);
	line(t1, t2, image, color);
	line(t2, t0, image, color);
}

int main(int argc, char** argv) {
	if (argc == 2) {
		model = new Model(argv[1]);
	}
	else {
		model = new Model("obj/head.obj");
	}

	TGAImage image(width, height, TGAImage::RGB);
	//image.set(52, 41, red);
	
	//drawRandomLines(10, image);	

	drawLineModel(image);

	//drawTriangle(Vec2i(10, 20), Vec2i(30, 30), Vec2i(50, 50), image, white);


	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	delete model;
	return 0;
}