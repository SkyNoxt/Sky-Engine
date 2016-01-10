
#include <iostream>
#include <fstream>

#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Camera/Camera.h>

#include <Geometry/Mesh.h>

/*inline
Vector3<float> mix(const Vector3<float> &a, const Vector3<float>& b, const float &mixValue) 
{ return a * (1 - mixValue) + b * mixValue; }*/

static inline
float clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }

/*void fresnel(const Vector3<float> &I, const Vector3<float> &N, const float &ior, float &kr) 
{ 
    float cosi = clamp(-1, 1, I.dot(N)); 
    float etai = 1, etat = ior; 
    if (cosi > 0) {  std::swap(etai, etat); } 
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi)); 
    // Total internal reflection
    if (sint >= 1) { 
        kr = 1; 
    } 
    else { 
        float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        kr = (Rs * Rs + Rp * Rp) / 2; 
    }
}*/

Mesh* mesh;

static Vector3<float> castRay(Ray &ray, Camera &camera, uint32_t depth)
{
	Vector3<float> hitColor = (ray.direction + Vector3<float>(1)) * 0.5;
	if(depth > 3) return hitColor;

	float distance;
	unsigned int index;
	Vector2<float> uv;

    if(mesh->intersect(ray, distance, index, uv))
    {
	    hitColor = Vector3<float>(uv.x, uv.y, 1 - uv.x - uv.y);
	}

	/*if(mesh->intersect(ray, distance, index, uv))
	{
        Vector3<float> hitPoint = ray.origin + ray.direction * distance;

        Vector3<float> n0 = mesh->vertexArray[index    ].normal;
        Vector3<float> n1 = mesh->vertexArray[index + 1].normal;
        Vector3<float> n2 = mesh->vertexArray[index + 2].normal;

        Vector3<float> N = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;

        Vector2<float> st0 = mesh->vertexArray[index].texCoord;
        Vector2<float> st1 = mesh->vertexArray[index + 1].texCoord;
        Vector2<float> st2 = mesh->vertexArray[index + 2].texCoord;

        Vector2<float> st = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2;

	    Vector3<float> reflectionDirection = ray.direction.reflect(N).normalize(); 
	    Vector3<float> refractionDirection = ray.direction.refract(N, 1).normalize(); 
	    Vector3<float> reflectionRayOrig = reflectionDirection.dot(N) < 0 ? 
	        hitPoint - N * 0.0001 : 
	        hitPoint + N * 0.0001; 
	    Vector3<float> refractionRayOrig = refractionDirection.dot(N) < 0 ? 
	        hitPoint - N * 0.0001 : 
	        hitPoint + N * 0.0001; 

        Ray refl = Ray(reflectionRayOrig, reflectionDirection);
        Ray refr = Ray(refractionRayOrig, refractionDirection);

	    Vector3<float> reflectionColor = castRay(refl, camera, depth + 1); 
	    Vector3<float> refractionColor = castRay(refr, camera, depth + 1); 
	    float kr; 
	    fresnel(ray.direction, N, 1, kr); 
	    hitColor = mix(hitColor, reflectionColor * kr + refractionColor * (1 - kr), 0.75); 

        float scale = 13; 
    	float pattern = (fmodf(st.x * scale, 1) > 0.5) ^ (fmodf(st.y * scale, 1) > 0.5); 
    	hitColor = mix(hitColor, hitColor * 0.8, pattern);
	}*/

    return hitColor;
}

static void render(Camera &camera, int width, int height)
{
	float level = 0;

    Vector3<float> *framebuffer = new Vector3<float>[width * height];

    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            Ray ray = camera.castRay(width, height, i, j);
            framebuffer[width * j + i] = castRay(ray, camera, level);
        }
        std::cout << j << std::endl;
    }

    // Save result to a PPM image (keep these flags if you compile under Windows)
	std::ofstream ofs("/home/nelson/Desktop/RayTrace.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (uint32_t i = 0; i < height * width; ++i) {
        char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();

    delete[] framebuffer;
}

int main (int argc, char *argv[])
{
	int imgWidth = 160;
	int imgHeight = 120;

	mesh = new Mesh();
	std::ifstream meshStream("/home/nelson/Desktop/ad.mesh", std::ios::in | std::ios::binary);
	meshStream.read((char*)&(mesh->numVertices), sizeof(mesh->numVertices));
	mesh->vertexArray = new Vertex[mesh->numVertices];
	meshStream.read((char*)mesh->vertexArray, sizeof(Vertex) * mesh->numVertices);

	Camera camera = Camera(1.0, 50.0393, imgWidth / (float)imgHeight);
	//camera.viewMatrix = Matrix4<float>(0.707107, -0.331295, 0.624695, 0, 0, 0.883452, 0.468521, 0, -0.707107, -0.331295, 0.624695, 0, -1.63871, -5.747777, -40.400412, 1).inverse();

    render(camera, imgWidth, imgHeight);

    return 0;
}
