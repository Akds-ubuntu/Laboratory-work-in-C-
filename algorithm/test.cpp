#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct point{

    double x;
    double y;

};
struct Vector{
    double x,y;
    Vector(point a,point b){
        x=b.x-a.x;
        y=b.y-a.y;
    }

};
double determinant (Vector a, Vector b){
    return a.x*b.y-a.y*b.x;
}

bool position(point p1,point p2,point q)//функция которая определяе позицию точки p относительно отрезка соеденяющего точки p1 и p2
{
    double R;
    R = (q.y - p1.y) * (p2.x - p1.x)- (q.x - p1.x) * (p2.y - p1.y) ;
    if(R<=0){
        return true;
    }
    else{
        return false;
    }
}

vector<point>sorting_points(vector<point>&a){
    for(int i=1;i<a.size();++i){
        if(a[i].x<a[0].x||(a[i].x==a[0].x && a[i].y<a[0].y)){
            swap(a[i],a[0]);
        }
    }
    sort(a.begin()+1,a.end(),[&](point k, point b)->bool{
        return determinant(Vector(a[0],k),Vector(a[0],b))<0;
    });
    return a;

}
int main(){
    vector<point> A={{2,0},{0,2},{2,2},{0,0}};
    A=sorting_points(A);
    for(int i=0;i<A.size();++i){
        cout<<i<<"="<<A[i].x<<" "<<A[i].y<<"\n";
    }


}