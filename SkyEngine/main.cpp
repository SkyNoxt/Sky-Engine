
#include <limits>
#include <iostream>
#include <fstream>

#include <Math/Vector3.h>
#include <Camera/Camera.h>

/*class Vertex
{
public:
	Vector3<float> position;
};

class Mesh
{
public:
	unsigned int numVertices;
	Vertex* vertexArray;

	void transform(Matrix4<float> matrix)
	{
		for(int i = 0; i < numVertices; ++i)
			vertexArray[i].position *= matrix;
	}
};*/

class Program
{



public:

	const float kInfinity = std::numeric_limits<float>::max();

	static inline
	float clamp(const float &lo, const float &hi, const float &v)
	{ return std::max(lo, std::min(hi, v)); }

	static Vector3<float> castRay(const Vector3<float> &orig, const Vector3<float> &dir, Camera &camera, uint32_t depth)
	{
	    Vector3<float> hitColor = (dir + Vector3<float>(1)) * 0.5;
	    return hitColor;
	}

	static void render(Camera &camera, int width, int height)
	{
	    Vector3<float> *framebuffer = new Vector3<float>[width * height];
	    Vector3<float> *pix = framebuffer;

	    Vector3<float> orig = Vector3<float> { camera.viewMatrix.wx, camera.viewMatrix.wy, camera.viewMatrix.wz };

	    for (uint32_t j = 0; j < height; ++j) {
	        for (uint32_t i = 0; i < width; ++i) {

	            //Maya Style
	            //float x = (2 * (i + 0.5) / (float)width - 1) * camera.scale;
	            //float y = (1 - 2 * (j + 0.5) / (float)height) * scale * 1 / camera.aspectRatio;

	            //Normal Style
	            float x = (2 * (i + 0.5) / (float)width - 1) * camera.aspectRatio * camera.scale;
	            float y = (1 - 2 * (j + 0.5) / (float)height) * camera.scale;

	            Vector3<float> dir = Vector3<float>(x, y, -1.0) * camera.viewMatrix;

	            dir = dir.normalize();
	            *(pix++) = castRay(orig, dir, camera, 0);
	        }
	    }

	    // Save result to a PPM image (keep these flags if you compile under Windows)
		std::ofstream ofs("/home/nelson/Desktop/refRayT.ppm", std::ios::out | std::ios::binary);
	    ofs << "P6\n" << width << " " << height << "\n255\n";
	    for (uint32_t i = 0; i < height * width; ++i) {
	        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
	        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
	        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
	        ofs << r << g << b;
	    }

	    ofs.close();

	    delete [] framebuffer;
	}
};

int main (int argc, char *argv[])
{
	int imgWidth = 640;
	int imgHeight = 480;

	Camera *camera = new Camera(1.0, 90.0, imgWidth / (float)imgHeight);
	//camera->viewMatrix.translate(1.0, 0.0, 0.0);

    // finally, render
    Program::render(*camera, imgWidth, imgHeight);

    return 0;
}
