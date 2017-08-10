
#include <iostream>
#include <memory.h>

#include <omp.h>

#include <Camera/Camera.h>
#include <Math/Vector3.h>

#include <Streams/FileStream.h>

#include <Geometry/Model.h>

#include <Shading/DeltaLight.h>

#include <Input/LinuxGamepad.h>

#include <FPS.h>

//OPenCV test
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Model* model;

Matrix4<>* modelMatrix;
bool mode = true;

Gamepad* gamepad;

static inline float clamp(const float& lo, const float& hi, const float& v)
{
	return std::max(lo, std::min(hi, v));
}

DeltaLight* light;
Vector3<>* lightDirection;

static Vector3<> castRay(Ray& ray, Camera& camera, unsigned int depth)
{
	//Inverse Ray Transform
	/*Matrix4<> rayMatrix = modelMatrix->inverse();
	Vector4<> rayOrigin = Vector4<>{ray.origin.x, ray.origin.y, ray.origin.z, 1.0} * rayMatrix;
	ray = Ray(Vector3<>{rayOrigin.x, rayOrigin.y, rayOrigin.z}, ray.direction * rayMatrix);*/

	Vector3<> hitColor = (ray.direction + Vector3<>{1}) * 0.5;

	float distance = Ray::MAX_LENGTH;
	unsigned int index;
	Vector2<> uv;

	float tempDistance;
	unsigned int tempIndex = -1;
	Vector2<> tempUV;
	bool intersect = false;
	int meshIndex;

	unsigned int numMeshes = model->numMeshes;
	IndexedMesh* meshes = model->meshArray;
	for(unsigned int i = 0; i < numMeshes; ++i)
		{
			if(meshes[i].intersect(ray, tempDistance, tempIndex, tempUV) && tempDistance > 0 && tempDistance < distance)
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
			//std::cout << index << std::endl;
			Vector3<> hitPoint = ray.origin + ray.direction * distance;

			Vector3<> n0 = meshes[meshIndex].vertexArray[index].normal;
			Vector3<> n1 = meshes[meshIndex].vertexArray[index + 1].normal;
			Vector3<> n2 = meshes[meshIndex].vertexArray[index + 2].normal;

			/*Vector3<> v0 = meshes[meshIndex]->vertexArray[index    ].position; 
    		Vector3<> v1 = meshes[meshIndex]->vertexArray[index + 1].position; 
    		Vector3<> v2 = meshes[meshIndex]->vertexArray[index + 2].position;*/

			//Face and vertex Normals
			//Vector3<> fN = (v1 - v0).cross(v2 - v0).normalize();
			Vector3<> vN = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;

			//Light direction (inverse ray transformed)
			//Vector3<> L = -(*lightDirection * modelMatrix->inverse());

			//Face ratio
			hitColor = std::max(0.f, vN.dot(-ray.direction));

			//Diffuse shading
			//hitColor = Vector3<>{0.18} * (1.0/M_PI) * light->intensity * light->color * std::max(0.f, vN.dot(L));
		}

	return hitColor;
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

#pragma omp parallel for num_threads(32)
	for(unsigned int j = 0; j < height; ++j)
		{
#pragma omp parallel for num_threads(32)
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

float min3(const float& a, const float& b, const float& c)
{
	return std::min(a, std::min(b, c));
}

float max3(const float& a, const float& b, const float& c)
{
	return std::max(a, std::max(b, c));
}

float frontFace(const Vector3<>& a, const Vector3<>& b, const Vector3<>& c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

float backFace(const Vector3<>& a, const Vector3<>& b, const Vector3<>& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static void rasterize(Camera& camera, int width, int height)
{
	Vector3<>* framebuffer = new Vector3<>[width * height];
	float* depthbuffer = new float[width * height];
	memset(depthbuffer, camera.farPlane, width * height * sizeof(float));

	Matrix4<> transform = camera.projectionMatrix * camera.viewMatrix * *modelMatrix;

#pragma omp parallel for num_threads(64)
	for(unsigned int m = 0; m < model->numMeshes; ++m)
		{
#pragma omp parallel for num_threads(512)
			for(unsigned int i = 0; i < model->meshArray[m].numElements(); ++i)
				{
					const Vector3<>& v0 = model->meshArray[m].getVertex(i).position;

					Vector4<> currentVertex = Vector4<>{ v0.x, v0.y, v0.z, 1.0 } * transform;

					Vector3<> v0Raster;

					if(rasterVertex(v0Raster, currentVertex, width, height))
						framebuffer[(int)v0Raster.y * width + (int)v0Raster.x] = 1.0;
				}
		}

	/*unsigned int tris = 0;
#pragma omp parallel for num_threads(64)
			for(unsigned int m = 0; m < model->numMeshes; ++m)
				{
					unsigned int numTriangles = model->meshArray[m].numElements() / 3;
#pragma omp parallel for num_threads(512)
					for(unsigned int i = 0; i < numTriangles; ++i)
						{
							const Vector3<>& v0 = model->meshArray[m].getVertex(i * 3).position;
							const Vector3<>& v1 = model->meshArray[m].getVertex(i * 3 + 1).position;
							const Vector3<>& v2 = model->meshArray[m].getVertex(i * 3 + 2).position;

							Vector4<> t0 = Vector4<>{ v0.x, v0.y, v0.z, 1.0 } * transform;
							Vector4<> t1 = Vector4<>{ v1.x, v1.y, v1.z, 1.0 } * transform;
							Vector4<> t2 = Vector4<>{ v2.x, v2.y, v2.z, 1.0 } * transform;

							//if(t0.w <= 0.0 || t1.w <= 0.0 || t2.w <= 0.0)
							{
								if(t0.w <= 0)
									t0.w = 0.0001;
								if(t1.w <= 0)
									t1.w = 0.0001;
								if(t2.w <= 0)
									t2.w = 0.0001;
							}
							if(t0.z < camera.nearPlane && t1.z < camera.nearPlane && t2.z < camera.nearPlane)
								continue;
							if(t0.z > camera.farPlane && t1.z > camera.farPlane && t2.z > camera.farPlane)
								continue;

							Vector3<> v0Raster = { t0.x, t0.y, -t0.z };
							v0Raster *= (1 / t0.w);
							v0Raster.x = ((v0Raster.x + 1) * 0.5 * width);
							v0Raster.y = ((1 - (v0Raster.y + 1) * 0.5) * height);
							Vector3<> v1Raster = { t1.x, t1.y, -t1.z };
							v1Raster *= (1 / t1.w);
							v1Raster.x = ((v1Raster.x + 1) * 0.5 * width);
							v1Raster.y = ((1 - (v1Raster.y + 1) * 0.5) * height);
							Vector3<> v2Raster = { t2.x, t2.y, -t2.z };
							v2Raster *= (1 / t2.w);
							v2Raster.x = ((v2Raster.x + 1) * 0.5 * width);
							v2Raster.y = ((1 - (v2Raster.y + 1) * 0.5) * height);

							float xmin = min3(v0Raster.x, v1Raster.x, v2Raster.x);
							float ymin = min3(v0Raster.y, v1Raster.y, v2Raster.y);
							float xmax = max3(v0Raster.x, v1Raster.x, v2Raster.x);
							float ymax = max3(v0Raster.y, v1Raster.y, v2Raster.y);

							//Partial triangle clipping
							if(xmin >= width || xmax < 0 || ymin >= height || ymax < 0)
								continue;
							//Full triangle clipping
							//if (xmin < 0 || xmax >= width || ymin < 0 || ymax >= height) continue;

							if(xmax >= width)
								xmax = width - 1;
							if(ymax >= height)
								ymax = height - 1;
							if(xmin < 0)
								xmin = 0;
							if(ymin < 0)
								ymin = 0;

							float (*edgeFunction)(const Vector3<>&, const Vector3<>&, const Vector3<>&) = &frontFace;
							float area = edgeFunction(v0Raster, v1Raster, v2Raster);
							if(area < 0)
								{
									area = -area;
									edgeFunction = &backFace;
								}

							tris++;

							for(uint32_t y = ymin; y <= ymax; ++y)
								{
									for(uint32_t x = xmin; x <= xmax; ++x)
										{
											Vector3<> pixelSample(x + 0.5, y + 0.5, 0);
											float w0 = edgeFunction(v1Raster, v2Raster, pixelSample);
											float w1 = edgeFunction(v2Raster, v0Raster, pixelSample);
											float w2 = edgeFunction(v0Raster, v1Raster, pixelSample);

											if(w0 >= 0 && w1 >= 0 && w2 >= 0)
												{
													w0 /= area;
													w1 /= area;
													w2 /= area;

													float oneOverZ = v0Raster.z * w0 + v1Raster.z * w1 + v2Raster.z * w2;
													float z = -(oneOverZ);
													if(z < -1 || z > 1)
														continue;
													if(z < depthbuffer[y * width + x])
														{
															depthbuffer[y * width + x] = z;
															framebuffer[y * width + x] = model->meshArray[m].getVertex(i * 3).normal;
														}
												}
										}
								}
						}
				}*/

	//std::cout << tris << std::endl;

	cv::Mat img(height, width, CV_32FC3, framebuffer);
	imshow("Sky Engine", img);
	cv::waitKey(1);

	delete[] framebuffer;
	delete[] depthbuffer;
}

int main(int argc, char* argv[])
{
	int imgWidth = 1280;
	int imgHeight = 720;

	//OpenCV window
	namedWindow("Sky Engine", cv::WINDOW_AUTOSIZE);

	Camera camera = Camera(1.0, 90, imgWidth / (float)imgHeight, 0.1, 100000000.0);
	model = new Model(FileStream("/home/nelson/Desktop/light.test"));

	//Instance gamepad
	gamepad = new LinuxGamepad();
	LinuxGamepad::State state;

	FPS* fps = new FPS(&camera, gamepad, 3.0, 3.0);

	//Compute transformation matrix
	modelMatrix = new Matrix4<>();
	//modelMatrix->scale(10, 10, 10);
	Matrix4<> normalMatrix = modelMatrix->inverse().transpose();

	/*//Forward Mesh Transformation
	for(unsigned int i = 0; i < mesh->numVertices; ++i)
	{
		mesh->vertexArray[i].position *= *modelMatrix;
		mesh->vertexArray[i].normal *= normalMatrix;
	}*/

	//Compute camera
	camera.viewMatrix = camera.cameraMatrix.inverse();

	//Compute light
	light = new DeltaLight(Vector3<>{ 1.0, 0.0, 0.0 }, 15);
	light->lightMatrix.translate(0.0, 0.0, 0.0); //Point light transform
	//light->lightMatrix.rotate(45, 1.0, 0.0, 0.0);
	lightDirection = new Vector3<>();
	*lightDirection = Vector3<>{ 0.0, 0.0, -1.0 } * light->lightMatrix;

	//Render
	while(true)
		{
			clock_t begin = clock();

			camera.viewMatrix = Matrix4<>::IDENTITY;

			gamepad->poll();
			fps->update();

			if(gamepad->state.buttons & Gamepad::BUTTON_RIGHT_SHOULDER)
				render(camera, imgWidth, imgHeight);
			else
				rasterize(camera, imgWidth, imgHeight);

			/*light->lightMatrix.rotate(1, 0.0, 1.0, 0.0);
			*lightDirection = Vector3<> { 0.0, 0.0, -1.0 } * light->lightMatrix;*/

			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			std::cout << "FPS: " << 1.0 / elapsed_secs << std::endl;
		}

	delete gamepad;

	return 0;
}
