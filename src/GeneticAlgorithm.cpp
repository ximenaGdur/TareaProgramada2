#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm (int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio)
: elitismRatio (elitismRatio)
, mutationRatio (mutationRatio)
, sporadicRatio (sporadicRatio)
, currentEpoch (1)
, populationSize (populationSize) { }
    
GeneticAlgorithm::~GeneticAlgorithm() { }

unsigned int GeneticAlgorithm::getEpoch() { return currentEpoch; }

void GeneticAlgorithm::reset(int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio)
{
    elitismRatio = elitismRatio;
    populationSize = populationSize;
    mutationRatio = mutationRatio;
    sporadicRatio = sporadicRatio;
    currentEpoch = 1;
}
