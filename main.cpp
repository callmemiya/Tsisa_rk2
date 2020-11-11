#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>

double func(double x, double y){
    return exp(-x*x-y*y);
}

struct Coords{
    double x,y;
    double fit;
};

std::vector<Coords> population;

double mid_value(const std::vector<Coords>& v){
    double res = 0.0;
    for (const auto& el : v){
        res += el.fit;
    }
    return res / 4;
}

bool CompareCoords(const Coords& c1, const Coords& c2){
    return c1.fit > c2.fit;
};

void print_results(const std::vector<Coords>& v, size_t it){
    std::cout << "N: " << it << " Average: " << mid_value(v) << " Max: " << v[0].fit << std::endl;
    for (const auto& el : v){
        std::cout << "x: " << el.x << " y: " << el.y << " fit: " << el.fit << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    population.resize(4);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_real_distribution<double> dis(-1, 1);
    std::uniform_real_distribution<double> dis_mut(-5, 5);
    std::uniform_real_distribution<double> prob(0, 1);
    int n = 100;
    double p_mut = 0.05;
    
    for (auto i = 0; i < population.size(); i++){
        Coords coord;
        coord.x = dis(mersenne);
        coord.y = dis(mersenne);
        coord.fit = func(coord.x, coord.y);
        population[i] = coord;
    }
    
    std::sort(population.begin(), population.end(), CompareCoords);
    print_results(population, 0);
    for (auto i = 1; i <= n; i++){
        for (auto j = 0; j < population.size(); j++){
            auto p = prob(mersenne);
            if (p < p_mut){
                population[j].x = fmod(population[j].x * dis_mut(mersenne), 1);
                population[j].y = fmod(population[j].y * dis_mut(mersenne), 1);
                population[j].fit = func(population[j].x, population[j].y);
            }
        }
        std::sort(population.begin(), population.end(), CompareCoords);
        std::vector<Coords> new_pop;
        new_pop.resize(4);
        size_t temp;
        if (population[0].fit != population[1].fit){
            temp = 1;
        } else {
            temp = 2;
        }
        new_pop[0].x = population[0].x;
        new_pop[0].y = population[temp].y;
        new_pop[0].fit = func(new_pop[0].x, new_pop[0].y);
    
        new_pop[1].x = population[temp].x;
        new_pop[1].y = population[0].y;
        new_pop[1].fit = func(new_pop[1].x, new_pop[1].y);
        
        new_pop[2].x = population[0].x;
        new_pop[2].y = population[temp + 1].y;
        new_pop[2].fit = func(new_pop[2].x, new_pop[2].y);
        
        new_pop[3].x = population[temp + 1].x;
        new_pop[3].y = population[0].y;
        new_pop[3].fit = func(new_pop[3].x, new_pop[3].y);
        
        std::sort(new_pop.begin(), new_pop.end(), CompareCoords);
        population = new_pop;
        print_results(population, i);
    }
    return 0;
}
