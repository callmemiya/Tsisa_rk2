#include <iostream>
#include <vector>
#include <random>
#include <time.h>

double func(double x, double y){
    return exp(-x*x-y*y);
}

struct individ{
    double x,y;
    double f;
};

double medium(std::vector<individ>& pop){
    double mid = 0;
    for (auto& i : pop){
        mid += i.f;
    }
    return mid / 4;
}

bool cmp(const individ& in, const individ& ind){
    return in.f > ind.f;
}

void print(std::vector<individ>& pop, int n){
    std::cout << "N = " <<n <<" Medium result = " <<medium(pop) <<" Maximum result = " <<pop[0].f <<std::endl;
    for (const auto& i : pop){
        std::cout <<"X = " <<i.x <<" Y = " <<i.y <<" F(x,y) = " <<i.f <<std::endl;
    }
}

int main() {
    std::mt19937 mersenne(time(0));
    std::vector<individ> popul(4);
    std::uniform_real_distribution<double> interval(-2, 2);
    std::uniform_real_distribution<double> mut(0, 1);
    double mutation = 0.4;
    for (int i = 0; i < 4; i++){
        individ new_ind;
        new_ind.x = interval(mersenne);
        new_ind.y = interval(mersenne);
        new_ind.f = func(new_ind.x, new_ind.y);
        popul[i] = new_ind;
    }
    int n = 100;
    std::sort(popul.begin(), popul.end(), cmp);
    print(popul, 0);
    for (int i = 1; i <= n; i++){
        for (auto j = 0; j < popul.size(); j++) {
            auto ch = mut(mersenne);
            if (ch < mutation) {
                popul[j].x = (popul[j].x + interval(mersenne)) / 2;
                popul[j].y = (popul[j].y + interval(mersenne)) / 2;
                popul[j].f = func(popul[j].x, popul[j].y);
            }
        }
        std::sort(popul.begin(), popul.end(), cmp);
        std::vector<individ> new_popul(4);
        int l;
        if (popul[0].f != popul[1].f){
             l = 1;
        } else {
             l = 2;
        }
        new_popul[0].x = popul[0].x;
        new_popul[0].y = popul[l].y;
        new_popul[0].f = func(new_popul[0].x, new_popul[0].y);
        new_popul[1].x = popul[l].x;
        new_popul[1].y = popul[0].y;
        new_popul[1].f = func(new_popul[1].x, new_popul[1].y);
        new_popul[2].x = popul[0].x;
        new_popul[2].y = popul[l+1].y;
        new_popul[2].f = func(new_popul[2].x, new_popul[2].y);
        new_popul[3].x = popul[l+1].x;
        new_popul[3].y = popul[0].y;
        new_popul[3].f = func(new_popul[2].x, new_popul[2].y);
        std::sort(new_popul.begin(), new_popul.end(), cmp);
        popul = new_popul;
        if (i % 10 == 0) print(popul, i);
    }
    return 0;
}
