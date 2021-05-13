#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

#include "Image.hpp"
#include "Vec3.hpp"

#define LIGHT_AMBIENT 0
#define LIGHT_POINT 1
#define LIGHT_DIRECTIONAL 2

using namespace std;

pix BLACK = {0,0,0};
pix WHITE = {255,255,255};
pix operator*(pix C, double k) {
    C.r*=k, C.g*=k, C.b*=k;
    return C;
}

double Dot(Vec3 A, Vec3 B);
double abs(Vec3 &V);

struct Sphere {
    Vec3 Center;
    double Radius;
    pix Color;
    double Specular;
};

struct Light {
    int type;
    double intensity;
    Vec3 position;
};


const double inf = 9e18;
double viewportHeight=1, viewportWidth=1.7;
double canvasHeight=600, canvasWidth=1000;
double ViewDist = 1;

void CanvasToViewport(Vec3 &D) {
    D.x = (viewportWidth*D.x)/canvasWidth;
    D.y = (viewportHeight*D.y)/canvasHeight;
    D.z = ViewDist;
}

void SolveQuad(double a, double b, double c, double &x1, double &x2) {
    double D = b*b - 4*a*c;
    if(D<0) {x1=x2=inf; return;}
    x1 = (-b+sqrt(D))/(2*a); 
    x2 = (-b-sqrt(D))/(2*a); 
}

void readSpheresFromFile(vector<Sphere> &ar) {
    ifstream fio("data.txt", ios::in);

    Vec3 Center;
    double Radius, Specular;
    pix Color;
    int R,G,B;

    while(fio) {
        fio >> Center.x >> Center.y >> Center.z;
        fio >> Radius;
        fio >> R >> G >> B;
        fio >> Specular;
        Color = {(uint8_t)R,(uint8_t)G,(uint8_t)B};
        Sphere S = {Center, Radius, Color, Specular};
        ar.push_back(S);
    }
    ar.pop_back();
    fio.close();
}

vector<Light> lights = { {0,0.2,{0,0,0}}, {1,0.6,{2,1,0}}, {2, 0.2, {1,4,4}} };

double ComputeShade(double t, Sphere &S, Vec3 &D) {
    Vec3 P = D*t;
    Vec3 N = P - S.Center;
    N /= abs(N);
    double i = 0.0;
    Vec3 Origin = {0,0,0};

    for(Light light: lights) {

        if(light.type == LIGHT_AMBIENT) {
            i += light.intensity;
        }
        else {
            Vec3 L = light.position;
            if(light.type == LIGHT_POINT) {
                L -= P;
            }

            double CosineofNL = Dot(L,N)/abs(L);
            if(CosineofNL > 0) {
                i += light.intensity*(CosineofNL);
            }

            Vec3 R = N*(Dot(L,N)*2); R -= L;
            Vec3 V = Origin - P;
            double CosineofRV = Dot(R,V)/(abs(R)*abs(V));
            if(CosineofRV > 0.0) {
                i += pow(CosineofRV, S.Specular) * light.intensity;
                if(i>1) i = 1;
            }
        }
    }
    return i;
}

void FindClosestSphere(vector<Sphere> spheres, pix &ClosestColor, Vec3& D) {
    
    double ClosestIntersection = inf;
    Sphere ClosestSphere;

    for(auto S: spheres) {

        // Solving equation: Ax^2 + Bx + C = 0
        double A = Dot(D,D);
        double B = -2*Dot(S.Center, D);
        double C = Dot(S.Center, S.Center) - S.Radius*S.Radius;

        double sol1, sol2;
        SolveQuad(A,B,C,sol1,sol2);

        if(sol1 >= 1.0 && sol1 < inf) {
            if(ClosestIntersection > sol1) {
                ClosestIntersection = sol1;
                ClosestSphere = S;
            }
        }

        if(sol2 >= 1.0 && sol2 < inf) {
            if(ClosestIntersection > sol2) {
                ClosestIntersection = sol2;
                ClosestSphere = S;
            }
        }
    }
    if(ClosestIntersection != inf) {
        double shade = ComputeShade(ClosestIntersection, ClosestSphere, D);
        ClosestColor = ClosestSphere.Color * shade;
    }
}

int main() {
    
    Image img("img.bmp", canvasHeight, canvasWidth, 255, 255, 255);

    vector<Sphere> spheres;
    readSpheresFromFile(spheres);

    for(double i=-canvasHeight/2; i<canvasHeight/2; ++i) {
        for(double j=-canvasWidth/2; j<canvasWidth/2; ++j) {

            Vec3 D = {j,i,0};
            CanvasToViewport(D);

            pix ClosestColor = {255,255,255};

            FindClosestSphere(spheres, ClosestColor, D);

            int X = j + canvasWidth/2;
            int Y = i + canvasHeight/2;

            img.SetPixel(X, Y, ClosestColor.r, ClosestColor.g, ClosestColor.b);
        }
    }

    img.Generate();

    return 0;
}
