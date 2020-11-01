#include "TravellingSalesman.h"

#include <cstdlib> 
#include <ctime>
#include <cmath> 

/******************************* Free Functions *******************************/

int generateRandomNumber (int first, int last)
{
    srand(time(NULL));
    return first + ( rand()%(last-first) );
}

float calculateHypotenuse (float x1, float x2, float y1, float y2) {
    return sqrt (pow(x2-x1,2) + pow(y2-y1,2));
}

template <typename data>
void swap (data* dat1, data* dat2)
{
    data temp = *dat1;
    *dat1 = *dat2;
    *dat2 = temp;
}

/********************************* Case Class *********************************/

Case::Case (float** cities) 
: amountCities (sizeof(cities)/sizeof(cities[0]))
, cities (cities)
, genome (new int[amountCities+1]) 
, fitness (calculateFitness())
{
    setGenome();
}

Case::~Case(){
    delete  genome;
}

float Case::calculateFitness()
{
    // Create fitness as 0
    float fitness = 0;
    // Repeat index for amountCities
    for (int index = 0; index < amountCities-1; index++)
    {
        // Create currentPosition as the value of genome [index]
        int currentPosition = genome [index];
        // Create x1 as the value of cities [currentPosition][0]
        float x1 = cities [currentPosition][0];
        // Create y1 as the value of cities [currentPosition][1]
        float y1 = cities [currentPosition][1];
        // Create x2 as the value of cities [currentPosition+1][0]
        float x2 = cities [currentPosition+1][0];
        // Create y2 as the value of cities [currentPosition+1][1]
        float y2 = cities [currentPosition+1][1];
        // Add to fitness the value of hypotenuse
        fitness += calculateHypotenuse (x1,x2,y1,y2);
    }
    // return fitness
    return fitness;
}

float Case::getFitness() {
    return fitness;
}

void Case::setGenome(){
    int e, g = 0;
    for(int i=0; i<amountCities; i++){
        g=i;
        e= generateRandomNumber(0, amountCities);
        for(int d=0;d<=g;d++){
            if(e==genome[d]){
                g=g-g;
                i=i-1;
            }
            while((g==i)&&(e!=genome[d])&&(d==i)){
                genome[i]=e;
            }
        }
    }
    genome[amountCities+1]=genome[0];
}


int* Case::getGenome() {
    return genome;
}

/************************** TravellingSalesman Class **************************/

TravellingSalesman::TravellingSalesman (float** cities, int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio)
: GeneticAlgorithm (populationSize, elitismRatio, mutationRatio, sporadicRatio)
, original (new Case* [populationSize])
, population (new Case* [populationSize]) 
, amountCities ( sizeof(cities) / sizeof(cities[0]) )
, cities (cities) { 
    for (int i=0; i<populationSize; i++)
        original[i] = new Case(cities); 
    sort(); 
    for (int i=0; i<populationSize; i++)
        population[i] = original[i];
}

TravellingSalesman::~TravellingSalesman () { 
    delete population; 
    delete original;
}

void TravellingSalesman::reset (int populationSize,float elitismRatio,float mutationRatio,float sporadicRatio)
{
    delete population;
    population = original;
    GeneticAlgorithm::reset(populationSize, elitismRatio, mutationRatio, sporadicRatio);
}

void TravellingSalesman::epoch()
{
    return;
}

float TravellingSalesman::getBestIndividual() { return population[0]->getFitness(); }

void TravellingSalesman::drawBestIndividual(float** points, unsigned int& numPoints)
{
    for (int i=0; i<amountCities; i++) {
        points[i][0] = cities [ population[0]->getGenome()[i] ][0];
        points[i][1] = cities [ population[0]->getGenome()[i] ][1];
        numPoints++;
    }
}

void TravellingSalesman::sort()
{
    bool swapped = false;
    for (int i = 0; i < populationSize-1; i++) { 
        swapped = false; 
        for (int j = 0; j < populationSize-i-1; j++){ 
            if (population[j]->getFitness() > population[j+1]->getFitness()){ 
                swap(population[j], population[j+1]); 
                swapped = true; 
            } 
        } 
        if (swapped == false) 
            return; 
    }   
}
