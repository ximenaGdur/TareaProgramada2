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
    // array size 'cities'
 public:
    /// Constructors
    Case(); //@author Jan Pablo Murillo - B95447 ^ int cities -> 'size'
    ~Case(); //@author Jan Pablo Murillo - B95447
    /// Methods
    float getFitness(); //@author Jimena Gdur - B93250
    int* getGenome(); //@author Jan Pablo Murillo - B95447
};

/************************** TravellingSalesman Class **************************/

class TravellingSalesman : public GeneticAlgorithm
{
 protected: //@author Jimena Gdur - B93250
    Case* population; 
    const Case* original;
    int amountCities;
    float** cities;
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
