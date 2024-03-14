#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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
double determinant(Vector a,Vector b){
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
vector<point>sorting_points(vector<point>&a){//функция котороя сортирует точки по часовой стрелке
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
//функция которая ищет точки пересечения прямых
point line_intersection (point p1,point p2,point p3,point p4)
{
    double x,y,m1,m2,b1,b2;
    if(p2.x-p1.x==0){
        x=p1.x;
        m2=(p4.y - p3.y) / (p4.x - p3.x);
        b2=p3.y-m2*p3.x;// y = m2 * x + b2
        y=m2*x+b2;
    }
    else if(p4.x-p3.x==0){
        x=p3.x;
        m1=(p2.y-p1.y)/(p2.x-p1.x);
        b1=p1.y-m1*p1.x;
        y=m1*x+b1;
    }
    else{
        m1 = (p2.y - p1.y) / (p2.x - p1.x);
        b1 = p1.y - m1 * p1.x;
        m2 = (p4.y - p3.y) / (p4.x - p3.x);
        b2 = p3.y - m2 * p3.x;
        x = (b2 - b1) / (m1 - m2);
        y = m1 * x + b1;
    }
    point intersection;
    intersection.x=x;
    intersection.y=y;
        
    return intersection;
}
int main()
{
    cout<<"Введите количество вершин у фигуры №1:"<<"\n";
    int size_1,size_2;
    point s,c;
    cin>>size_1;//вводим количество точек для первой фигуры
    vector<point>S(size_1);//объявляем вектор для фигуры S
    cout<<"Введите вершины:"<<"\n";
    for(int i=0;i<size_1;++i){//заполняем вектор точками
        cin>>s.x >>s.y;
        S.push_back(s);
    }
   // vector<point>S= {{-1,1},{1,-1},{1,1},{-1,-1}};
    S=sorting_points(S);//сортируем точки по часовой внутри вектора
    cout<<"Введите количество вершин у фигуры №2:"<<"\n";
     cin>>size_2;//вводим количество точек для C фигуры
    //vector<point>C={{0,0},{2,2},{0,2},{2,0}};
    vector<point>C(size_2);//объявляем вектор для C фигуры
    cout<<"Введите вершины:"<<"\n";
    for(int i=0;i<size_2;++i){//заполняем вектор точками
        cin>>c.x >>c.y;
        C.push_back(c);
    }
    C=sorting_points(C);//сортируем точки
    vector<point>output=S;
    int N=S.size();
    int M=C.size();
    for(int i=1;i<=M;++i){//цикл который проходит по точкам фигуры C
        vector<point>input=output;
        output.clear();
        if(i==M){//Эта штука нужна для того что бы обрабатывать последний отрезок
            point c_2=C[0];
            point c_1=C[i-1];
            for(int j=1;j<=input.size();++j){//этот цикл идёт по точкам фигуры S
                if(j==input.size()){//Эта штука нужна для того что бы обрабатывать последний отрезок
                    point s_1=input[j-1];
                    point s_2=input[0];
                    if(position(c_1,c_2,s_2)){//это if и else определяют как раз положение точек в пространстве
                        if(!position(c_1,c_2,s_1)){
                            output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                        }
                        output.push_back(s_2);
                    }
                    else if(position(c_1,c_2,s_1)){
                        output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                    }
                }
            else{//всё тоже самое что и в if
                point s_1=input[j-1];
                point s_2=input[j];
                if(position(c_1,c_2,s_2)){
                    if(!position(c_1,c_2,s_1)){
                        output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                    }
                    output.push_back(s_2);
                }
                else if(position(c_1,c_2,s_1)){
                    output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                }
            }
        }
        }else//тоже самое что и в if
        {
            point c_2=C[i];
            point c_1=C[i-1];
            for(int j=1;j<=input.size();++j){
                if(j==input.size()){
                    point s_1=input[j-1];
                    point s_2=input[0];
                    if(position(c_1,c_2,s_2)){
                        if(!position(c_1,c_2,s_1)){
                            output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                        }
                        output.push_back(s_2);
                    }
                    else if(position(c_1,c_2,s_1)){
                        output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                    }
                }
            else{
                point s_1=input[j-1];
                point s_2=input[j];
                if(position(c_1,c_2,s_2)){
                    if(!position(c_1,c_2,s_1)){
                        output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                    }
                    output.push_back(s_2);
                }
                else if(position(c_1,c_2,s_1)){
                    output.push_back(line_intersection(s_1,s_2,c_1,c_2));
                }
            }
        }
        }
    }
    cout<<"\n";
    for(int i=0;i<output.size();++i){
         cout<<"Точка№"<<i+1<<"="<<"("<<output[i].x<<","<<output[i].y<<")"<<"\n";
    }
    double Square=0;//Площадь получившейся из пересечения фигуры 
    for(int i=0;i<(output.size()-1);++i)
    {
        Square+=output[i].x*output[i+1].y;
        Square-=output[i].y*output[i+1].x;
    }
    Square+=output[output.size()-1].x*output[0].y-output[0].x*output[output.size()-1].y;
    Square=abs(Square/2);//вычесленная площадь
    cout<<"Площадь получившейся из пересечения фигуры:"<<" "<<Square<<"\n";
    



}