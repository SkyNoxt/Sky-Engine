
#include <chrono>
#include <iostream>
#include <thread>

#include <Camera/Camera.h>

#include <Streams/FileStream.h>

#include <Geometry/Model.h>
#include <Shading/Sampler.h>

#include <Input/Gamepad.h>

#include <FPS.h>

// OPenCV test
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Gamepad* gamepad;
FPS* fps;

Model* model;
Sampler* texture;

Matrix4<>* modelMatrix;

static Vector3<> castRay(Ray& ray, Camera& camera, unsigned int depth)
{
	// Inverse Ray Transform
	/*Matrix4<> rayMatrix = modelMatrix->inverse();
	Vector4<> rayOrigin = Vector4<>{ray.origin.x, ray.origin.y, ray.origin.z, 1.0} * rayMatrix;
	ray = Ray({rayOrigin.x, rayOrigin.y, rayOrigin.z}, ray.direction * rayMatrix);*/

	Vector3<> hitColor = (ray.direction + Vector3<>{ 1 }) * 0.5;

	float distance = Ray::MAX_LENGTH;
	unsigned int index;
	Vector2<> uv;

	float tempDistance;
	unsigned int tempIndex = -1;
	Vector2<> tempUV;
	bool intersect = false;
	int meshIndex;

	unsigned int numMeshes = model->numMeshes;
	Mesh* meshes = model->meshArray;
	for(unsigned int i = 0; i < numMeshes; ++i)
	{
		if(meshes[i].intersect<Vertex>(ray, tempDistance, tempIndex, tempUV) && tempDistance > 0 && tempDistance < distance)
		{
			meshIndex = i;
			distance = tempDistance;
			index = tempIndex;
			uv = tempUV;
			intersect = true;
		}
	}

	if(intersect)
	{
		// std::cout << index << std::endl;
		// Vector3<> hitPoint = ray.origin + ray.direction * distance;

		/*Vector3<> n0 = meshes[meshIndex].vertex<Vertex>(index).normal;
			Vector3<> n1 = meshes[meshIndex].vertex<Vertex>(index + 1).normal;
			Vector3<> n2 = meshes[meshIndex].vertex<Vertex>(index + 2).normal;*/

		/*Vector3<> v0 = meshes[meshIndex]->vertexArray[index    ].position;
			Vector3<> v1 = meshes[meshIndex]->vertexArray[index + 1].position;
			Vector3<> v2 = meshes[meshIndex]->vertexArray[index + 2].position;*/

		// Face and vertex Normals
		// Vector3<> fN = (v1 - v0).cross(v2 - v0).normalize();
		// Vector3<> vN = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;
		Vector2<> txc = (1 - uv.x - uv.y) * meshes[meshIndex].vertex<Vertex>(index).texCoord + uv.x * meshes[meshIndex].vertex<Vertex>(index + 1).texCoord + uv.y * meshes[meshIndex].vertex<Vertex>(index + 2).texCoord;

		// Light direction (inverse ray transformed)
		// Vector3<> L = -(*lightDirection * modelMatrix->inverse());

		// Texture mapping
		txc.y = txc.y - (int)txc.y;

		unsigned int xx = txc.x * texture->width;
		unsigned int yy = txc.y * texture->height;

		Vector4<unsigned char>& texel = texture->sample<Vector4<unsigned char>>(xx, yy);
		hitColor = Vector3<>{ texel.z / 255.0f, texel.y / 255.0f, texel.x / 255.0f };

		// Face ratio
		// hitColor = std::max(0.f, vN.dot(-ray.direction));

		// Diffuse shading
		// hitColor = Vector3<>{0.18} * (1.0/M_PI) * light->intensity * light->color * std::max(0.f, vN.dot(L));
	}

	return hitColor;
}

static void rasterLine(Vector3<> one, Vector3<> two, Sampler& framebuffer)
{
	int length = abs(two.x - one.x);
	int yLen = abs(two.y - one.y);

	if(yLen > length)
		length = yLen;

	Vector3<> increment = (two - one) * (1.0 / length);

	Vector3<> current = { one.x + 0.5, one.y + 0.5, one.z + 0.5 };
	for(int i = 1; i <= length; ++i)
	{
		framebuffer.sample<Vector4<unsigned char>>(current.x, current.y) = Vector4<unsigned char>{ 0, 0, 255, 255 };
		current += increment;
	}
}

static bool rasterVertex(Vector3<>& raster, const Vector4<>& vertex, unsigned int width, unsigned int height)
{
	raster = { vertex.x, vertex.y, -vertex.z };

	raster.x /= vertex.w;
	if(raster.x > 1.0 || raster.x < -1.0)
		return false;
	raster.y /= vertex.w;
	if(raster.y > 1.0 || raster.y < -1.0)
		return false;
	raster.z /= vertex.w;
	if(raster.z > 1.0 || raster.z < -1.0)
		return false;

	raster.x = ((raster.x + 1) * 0.5 * width);
	raster.y = ((1 - (raster.y + 1) * 0.5) * height);

	return true;
}

static void render(Camera& camera, unsigned int width, unsigned int height)
{
	float level = 0;

	Vector3<>* framebuffer = new Vector3<>[width * height];

	for(unsigned int j = 0; j < height; ++j)
	{
		for(unsigned int i = 0; i < width; ++i)
		{
			Ray ray = camera.castRay(width, height, i, j);
			framebuffer[width * j + i] = castRay(ray, camera, level);
		}
	}

	cv::Mat img(height, width, CV_32FC3, framebuffer);
	imshow("Sky Engine", img);
	cv::waitKey(1);

	delete[] framebuffer;
}

float frontFace(const Vector3<>& a, const Vector3<>& b, const Vector3<>& c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

float backFace(const Vector3<>& a, const Vector3<>& b, const Vector3<>& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Sampler framebuffer = Sampler(4, 1280, 720, 1, 1, 0);
float depthbuffer[1280 * 720];

static void rasterize(Camera& camera, int width, int height)
{
	memset(framebuffer.samples, 0, framebuffer.size * framebuffer.width * framebuffer.height);
	for(int i = 0; i < width * height; ++i)
		depthbuffer[i] = camera.farPlane;

	Matrix4<> transform = camera.projectionMatrix * camera.viewMatrix * *modelMatrix;

	for(unsigned int m = 0; m < model->numMeshes; ++m)
	{
		unsigned int numTriangles = model->meshArray[m].numElements() / 3;
		for(unsigned int i = 0; i < numTriangles; ++i)
		{
			const Vertex& v0 = model->meshArray[m].vertex<Vertex>(i * 3);
			const Vertex& v1 = model->meshArray[m].vertex<Vertex>(i * 3 + 1);
			const Vertex& v2 = model->meshArray[m].vertex<Vertex>(i * 3 + 2);

			const Vector3<>& p0 = v0.position;
			const Vector3<>& p1 = v1.position;
			const Vector3<>& p2 = v2.position;

			Vector4<> t0 = Vector4<>{ p0.x, p0.y, p0.z, 1.0 } * transform;
			Vector4<> t1 = Vector4<>{ p1.x, p1.y, p1.z, 1.0 } * transform;
			Vector4<> t2 = Vector4<>{ p2.x, p2.y, p2.z, 1.0 } * transform;

			if(t0.w < 0.0 || t1.w < 0.0 || t2.w < 0.0)
				continue;
			if(t0.z > t0.w || t1.z > t1.w || t2.z > t2.w)
				continue;

			Vector3<> r0 = { t0.x, t0.y, t0.z };
			r0 *= (1 / t0.w);
			r0.x = ((r0.x + 1) * 0.5 * width);
			r0.y = ((1 - (r0.y + 1) * 0.5) * height);

			Vector3<> r1 = { t1.x, t1.y, t1.z };
			r1 *= (1 / t1.w);
			r1.x = ((r1.x + 1) * 0.5 * width);
			r1.y = ((1 - (r1.y + 1) * 0.5) * height);

			Vector3<> r2 = { t2.x, t2.y, t2.z };
			r2 *= (1 / t2.w);
			r2.x = ((r2.x + 1) * 0.5 * width);
			r2.y = ((1 - (r2.y + 1) * 0.5) * height);

			float xmin = std::min({ r0.x, r1.x, r2.x });
			float ymin = std::min({ r0.y, r1.y, r2.y });
			float xmax = std::max({ r0.x, r1.x, r2.x });
			float ymax = std::max({ r0.y, r1.y, r2.y });

			// Partial triangle clipping
			if(xmin >= width || xmax < 0 || ymin >= height || ymax < 0)
				continue;
			// Full triangle clipping
			// if (xmin < 0 || xmax >= width || ymin < 0 || ymax >= height) continue;

			if(xmax >= width)
				xmax = width - 1;
			if(ymax >= height)
				ymax = height - 1;
			if(xmin < 0)
				xmin = 0;
			if(ymin < 0)
				ymin = 0;

			float area = frontFace(r0, r1, r2);
			if(area <= 0)
				continue;
			// float (*edgeFunction)(const Vector3<>&, const Vector3<>&, const Vector3<>&) = &frontFace;
			// float area = edgeFunction(r0, r1, r2);
			/*if(area < 0)
						{
							area = -area;
							edgeFunction = &backFace;
						}*/

			for(unsigned int y = ymin; y <= ymax; ++y)
			{
				for(unsigned int x = xmin; x <= xmax; ++x)
				{
					Vector3<> pixelSample(x + 0.5, y + 0.5, 0);
					float w0 = frontFace(r1, r2, pixelSample);
					float w1 = frontFace(r2, r0, pixelSample);
					float w2 = frontFace(r0, r1, pixelSample);

					if(w0 >= 0 && w1 >= 0 && w2 >= 0)
					{
						w0 /= area;
						w1 /= area;
						w2 /= area;

						float z = r0.z * w0 + r1.z * w1 + r2.z * w2;

						Vector3<> persp = { w0 /= t0.w, w1 /= t1.w, w2 /= t2.w };
						persp = (1.0f / (persp.x + persp.y + persp.z)) * persp;
						w0 = persp.x;
						w1 = persp.y;
						w2 = persp.z;

						/*if(z < -1 || z > 1)
												continue;*/

						if(z < depthbuffer[y * width + x])
						{
							depthbuffer[y * width + x] = z;

							Vector2<> uv0 = v0.texCoord;
							Vector2<> uv1 = v1.texCoord;
							Vector2<> uv2 = v2.texCoord;

							Vector2<> uv = uv0 * w0 + uv1 * w1 + uv2 * w2;

							uv.y = uv.y - (int)uv.y;

							const Vector4<unsigned char>& texel = texture->sample<Vector4<unsigned char>>(uv.x * texture->width, uv.y * texture->height);
							framebuffer.sample<Vector4<unsigned char>>(x, y) = Vector4<unsigned char>{ texel.z, texel.y, texel.x, 255 };
						}
					}
				}
			}
		}
	}

	cv::Mat img(height, width, CV_8UC4, framebuffer.samples);
	imshow("Sky Engine", img);
	cv::waitKey(1);
}

bool running = true;

int main(int argc, char* argv[])
{
	int imgWidth = 1280;
	int imgHeight = 720;

	// OpenCV window
	namedWindow("Sky Engine", cv::WINDOW_NORMAL);
	cv::resizeWindow("Sky Engine", imgWidth, imgHeight);

	framebuffer.samples = (unsigned char*)calloc(1, imgWidth * imgHeight * 4);

	Camera camera = Camera(1.0, 90, imgWidth / (float)imgHeight, 0.1, 200.0);
	model = new Model(FileStream("/home/sky/Documents/Other/sky/Models/Artisans/Artisans Hub.dat"));
	texture = new Sampler(FileStream("/home/sky/Documents/Other/sky/Models/Artisans/Artisans Hub.tex"));

	// Instance gamepad
	gamepad = new Gamepad();
	fps = new FPS(&camera, gamepad);

	// Compute transformation matrix
	modelMatrix = new Matrix4<>();

	// Compute camera
	camera.viewMatrix = camera.cameraMatrix.inverse();

	// Input thread
	std::thread input = std::thread(
		[]()
		{
			while(running)
				gamepad->poll();
		});

	// Game logic thread
	std::thread logic = std::thread(
		[]()
		{
			while(running)
			{
				auto next = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
				fps->update();
				std::this_thread::sleep_until(next);
			}
		});

	// Rendering (main) thread
	while(running)
	{
		auto start = std::chrono::steady_clock::now();
		auto next = start + std::chrono::milliseconds(32);

		if(gamepad->state.buttons & Gamepad::BUTTON_RIGHT_SHOULDER)
			render(camera, imgWidth, imgHeight);
		else
			rasterize(camera, imgWidth, imgHeight);

		auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start);
		printf("Graphics: %f\n", 1000000000.0 / ms.count());

		if(gamepad->state.buttons & Gamepad::BUTTON_A)
			running = false;

		std::this_thread::sleep_until(next);
	}

	logic.join();
	input.join();

	delete gamepad;

	return 0;
}
