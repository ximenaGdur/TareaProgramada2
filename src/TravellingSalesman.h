#ifndef TRAVELLING_SALESMAN_H
#define TRAVELLING_SALESMAN_H

#include "GeneticAlgorithm.h"

class TravellingSalesman : public GeneticAlgorithm
{
 public:
    TravellingSalesman (int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio);
    void reset ();
    void epoch ();
    float getBestIndividual ();
    void drawBestIndividual (float** points,unsigned int& numPoints);
};

#endif //TRAVELLING_SALESMAN_H
