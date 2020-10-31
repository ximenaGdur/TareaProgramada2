#ifndef TRAVELLING_SALESMAN_H
#define TRAVELLING_SALESMAN_H

#include <cstdlib> 
#include <ctime>

#include "GeneticAlgorithm.h"

/********************************* Case Class *********************************/

class Case
{
 private: //@author Jan Pablo Murillo - B95447
    /// Atributes
    int* genome;
    float fitness;
    int amountCities;
 public:
    /// Constructors
    Case(int amountCities=0); //@author Jan Pablo Murillo - B95447
    ~Case(); //@author Jan Pablo Murillo - B95447
    /// Methods
    void setGenome(); //@author Jan Pablo Murillo - B95447
    float getFitness(); //@author Jimena Gdur - B93250
    int* getGenome(); //@author Jan Pablo Murillo - B95447
 private:
    inline float calculateFitness() //@author Jimena Gdur - B93250
    {
        float fitness=0;
        return fitness;
    }
};

/************************** TravellingSalesman Class **************************/

class TravellingSalesman : public GeneticAlgorithm
{
 protected: 
    Case* population; //@author Jimena Gdur - B93250
    const Case* original; //@author Jimena Gdur - B93250
    int amountCities; //@author Jan Pablo Murillo - B95447
    float** cities; //@author Jimena Gdur - B93250
 public:       
    TravellingSalesman (float** cities, int populationSize, float elitismRatio, float mutationRatio, float sporadicRatio); //@author Jimena Gdur - B93250
    ~TravellingSalesman (); //@author Jimena Gdur - B93250
    void reset (int populationSize,float elitismRatio,float mutationRatio,float sporadicRatio); //@author Jimena Gdur - B93250
    void epoch (); //@author Jan Pablo Murillo - B95447
    float getBestIndividual (); //@author Jimena Gdur - B93250
    void drawBestIndividual (float** points, unsigned int& numPoints); //@author Jimena Gdur - B93250
    void sort(); //@author Jan Pablo Murillo - B95447
    //int checkFor (int number);
    void select();
    void crossover();
    void mutate();
};

/******************************* Free Functions *******************************/

int generateRandomNumber (int first, int last); //@author Jimena Gdur - B93250
int checkFor (int number); //@author Jimena Gdur - B93250

#endif //TRAVELLING_SALESMAN_H
