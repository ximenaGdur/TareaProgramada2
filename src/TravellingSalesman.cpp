#include "TravellingSalesman.h"

/********************************* Case Class *********************************/

Case::Case (int amountCities) 
: amountCities (amountCities)
, genome (new int[amountCities]) 
, fitness (calculateFitness())
{
    setGenome();
}

Case::~Case(){
    delete  genome;
}


float Case::getFitness()
{
    return fitness;
}

void Case::setGenome(){
    int e, g;
    srand(time(NULL));
    for(int i=0; i<amountCities; i++){
        g=i;
        e= generateRandomNumber(0, amountCities);
        for(int d=0;d<=g;d++){
            if(e==genome[d]){
                g=g-g;
                i=i-1;;
            }
            while((g==i)&&(e!=genome[d])&&(d==i)){
                genome[i]=e;
            }
        }
    }
    genome[amountCities+1]=genome[0];
}


int* Case::getGenome()
{
    return genome;
}

/************************** TravellingSalesman Class **************************/

TravellingSalesman::TravellingSalesman (float** cities, int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio)
: GeneticAlgorithm (populationSize, elitismRatio, mutationRatio, sporadicRatio)
, original (new Case(populationSize) [populationSize])
, population (new Case [populationSize]) 
, amountCities ( sizeof(cities) / sizeof(cities[0]) )
, cities (cities) { 
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
    population = (Case*) original;
    GeneticAlgorithm::reset(populationSize, elitismRatio, mutationRatio, sporadicRatio);
    return;
}

void TravellingSalesman::epoch()
{
    return;
}

float TravellingSalesman::getBestIndividual() { return population[0].getFitness(); }

void TravellingSalesman::drawBestIndividual(float** points, unsigned int& numPoints)
{
    for (int i=0; i<amountCities; i++) {
        points[i][0] = cities [ population[0].getGenome()[i] ][0];
        points[i][1] = cities [ population[0].getGenome()[i] ][1];
        numPoints++;
    }
}

void TravellingSalesman::sort()
{
    
}

/*
template <typename dataType>
int checkFor (dataType data, dataType* array, int size)
{
    for (int index = 0; index < size; index++)
    {
        if (array[index] == data) {
            return index;
        } else {
            return -1;
        }
    }
}
*/

/******************************* Free Functions *******************************/

int generateRandomNumber (int first, int last)
{
    srand(time(NULL));
    return first + ( rand()%(last-first) );
}
