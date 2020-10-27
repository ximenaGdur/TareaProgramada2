#include "GeneticAlgorithm.h"
#include "TravellingSalesman.h"

TravellingSalesman::TravellingSalesman (int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio)
: GeneticAlgorithm (populationSize, elitismRatio, mutationRatio, sporadicRatio)
{
    
}

void TravellingSalesman::reset ()
{
    return;
}

void TravellingSalesman::epoch()
{
    return;
}

float TravellingSalesman::getBestIndividual()
{
    return 0;
}
void TravellingSalesman::drawBestIndividual(float** points,unsigned int &numPoints)
{
    return;
}
