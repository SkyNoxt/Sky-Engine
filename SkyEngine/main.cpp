
#include <limits>
#include <iostream>
#include <fstream>

#include <Math/Vector2.h>
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

class Sphere
{

public:

    float radius, radius2;
    Vector3<float> center;
    Vector3<float> color = Vector3<float> { 0.1, 0.5, 0.3};

    Sphere(const Vector3<float> &c, const float &r) : radius(r), radius2(r *r ), center(c) {}

    bool intersect(const Ray &ray, float &t) const
    {
        float t0, t1; // solutions for t if the ray intersects

        // analytic solution
        Vector3<float> L = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2 * ray.direction.dot(L);
        float c = L.dot(L) - radius2;

        if (!solveQuadratic(a, b, c, t0, t1)) return false;

        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1; // if t0 is negative, let's use t1 instead
            if (t0 < 0) return false; // both t0 and t1 are negative
        }

        t = t0;

        return true;
    }

    void getSurfaceData(const Vector3<float> &Phit, Vector3<float> &Nhit, Vector2<float> &tex) const
    {
        Nhit = Phit - center; 
        Nhit.normalize(); 
        // In this particular case, the normal is simular to a point on a unit sphere
        // centred around the origin. We can thus use the normal coordinates to compute
        // the spherical coordinates of Phit.
        // atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
        // acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
        tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5; 
        tex.y = acosf(Nhit.y) / M_PI; 
    }

private:
	static bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
	{
	    float discr = b * b - 4 * a * c;
	    if (discr < 0) return false;
	    else if (discr == 0) {
	        x0 = x1 = - 0.5 * b / a;
	    }
	    else {
	        float q = (b > 0) ?
	            -0.5 * (b + sqrt(discr)) :
	            -0.5 * (b - sqrt(discr));
	        x0 = q / a;
	        x1 = c / q;
	    }

	    return true;
	}

};

Sphere* sphere;

float bias = 0.00001;

inline 
Vector3<float> mix(const Vector3<float> &a, const Vector3<float>& b, const float &mixValue) 
{ return a * (1 - mixValue) + b * mixValue; } 

static inline
float clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }

void fresnel(const Vector3<float> &I, const Vector3<float> &N, const float &ior, float &kr) 
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
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
} 

static Vector3<float> castRay(Ray &ray, Camera &camera, uint32_t depth)
{
	Vector3<float> hitColor = (ray.direction + Vector3<float>(1)) * 0.5;
	if(depth > 1) return hitColor;

	float f = 0;
	if(sphere->intersect(ray, f))
	{
        Vector3<float> hitPoint = ray.origin + ray.direction * f; 
        Vector3<float> N; // normal 
        Vector2<float> st; // st coordinates 
        sphere->getSurfaceData(hitPoint, N, st); 

	    Vector3<float> reflectionDirection = ray.direction.reflect(N).normalize(); 
	    Vector3<float> refractionDirection = ray.direction.refract(N, 1).normalize(); 
	    Vector3<float> reflectionRayOrig = reflectionDirection.dot(N) < 0 ? 
	        hitPoint - N * bias : 
	        hitPoint + N * bias; 
	    Vector3<float> refractionRayOrig = refractionDirection.dot(N) < 0 ? 
	        hitPoint - N * bias : 
	        hitPoint + N * bias; 

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
	}

    return hitColor;
}

static void render(Camera &camera, int width, int height)
{
	float level = 0;

    Vector3<float> *framebuffer = new Vector3<float>[width * height];
    Vector3<float> *pix = framebuffer;

    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {

            Ray ray = camera.castRay(width, height, i, j);
            *(pix++) = castRay(ray, camera, level);
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

int main (int argc, char *argv[])
{
	int imgWidth = 1920;
	int imgHeight = 1080;

	sphere = new Sphere(Vector3<float> { 0.0, 0.0, -1.5 }, 1.0);

	Camera *camera = new Camera(1.0, 90.0, imgWidth / (float)imgHeight);
	//camera->viewMatrix.rotate(45.0, 0.0, 0.0, 1.0);

    // finally, render
    render(*camera, imgWidth, imgHeight);

    return 0;
}
