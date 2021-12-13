// Imagine++ project
// Project:  Tp4_Initial
// Student(s): 

#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cmath>
#include <cstdlib>
#include <ctime>
#include<iostream>
using namespace std;

const int width = 512;
const int height = 512;
const int freqDisplay = 100;
const double dt = 1.;

void shock(double x,  double y,  double &vx,  double &vy,  double m,
           double x2, double y2, double &vx2, double &vy2, double m2) {
    double vvx = (m * vx + m2 * vx2)/(m + m2);
    double vvy = (m * vy + m2 * vy2)/(m + m2);
    double deltax = x2 - x;
    double deltay = y2 - y;
    double norme = deltax * deltax + deltay * deltay;
    double scal = -2. * ((vx-vvx)*deltax + (vy-vvy)*deltay)/norme;
    vx += scal * deltax;
    vy += scal * deltay;
    scal = -2. * ((vx2-vvx)*deltax + (vy2-vvy)*deltay)/norme;
    vx2 += scal * deltax;
    vy2 += scal * deltay;
}

void shockSimple(double x,  double y,  double &vx, double &vy, double m,
                 double x2, double y2, double vx2, double vy2) {
    shock(x,y,vx,vy,m,x2,y2,vx2,vy2,1000*m);
}

bool collision(double x1, double y1, double vx1, double vy1, double r1,
               double x2, double y2, double vx2, double vy2, double r2) {
    double dx=x1-x2,dy=y1-y2,dvx=vx1-vx2,dvy=vy1-vy2,r=r1+r2;
    if(dvx*dvx + dvy*dvy != 0) {
        double t_min = -(dx*dvx + dy*dvy)/(dvx*dvx + dvy*dvy);
        double t_true;
        if (t_min < 0)
            t_true = 0;
        else if (t_min > dt)
            t_true = dt;
        else
            t_true = t_min;
        dx += dvx * t_true;
        dy += dvy * t_true;
    }
    return ((dx*dx + dy*dy) <= r*r);
}

/////////////////////////////////////////////
int main() {
    openWindow(width, height);
    initRandom();

    //****************** INITIALIZATION *******************
    double x = width/10., y = height * 9. / 10;
    double vx = 0.1,vy = - 0.04;
    double r = 3;
    Color col = RED;
    //******* Save position for display ********
    double ox = x, oy = y;
    //****** Main loop ******
    for(int timeStep=0; timeStep<10000*freqDisplay; timeStep++) {
        //******** Display ************
        if ((timeStep%freqDisplay)==0){
            noRefreshBegin();
            fillCircle(int(ox),int(oy),int(r),WHITE);
            fillCircle(int(x),int(y),int(r),col);
            ox=x;oy=y;
            noRefreshEnd();
            milliSleep(50);
        }
        x+=vx*dt;
        y+=vy*dt;
    }
    endGraphics();
    return 0;
}
