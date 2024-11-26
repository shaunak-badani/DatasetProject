#include <iostream>
#include "math.h"
#include <vector>
#include <random>
#include <fstream>

/**
 * This class defines the system to be used for the simulation
 * It takes a number of parameters:
 * k -> Spring constant of the potential well
 * beta -> 1 / (kB * T), a thermodynamic variable inversely proportional to temperature.
 * gamma -> constant
 * u -> rate of change of center of harmonic potential
 */
class BrownianSystem
{
    private:
        float k, beta, gamma, u;
    public:
        BrownianSystem(float k, float beta, float gamma, float u)
        {
            this->k = k;
            this->beta = beta;
            this->gamma = gamma;
            this->u = u;
        }

        float U(float x, float lamda)
        {
            return 0.5 * k * pow(x - lamda, 2);
        }


        std::pair<std::vector<float>, float> runSimulation(float initialPos, float initialLamda, 
                int numSteps, float timeStep)
        {
            float dt = timeStep;
            float lamda = initialLamda;
            float workPerformed = 0;
            float x = initialPos + initialLamda;

            // Create a random number engine
            std::random_device rd{};
            std::mt19937 generator{rd()}; 

            // Define the distribution
            std::normal_distribution<double> distribution{0.0, 1.0}; 
            
            float standardDeviation = sqrt(2 * dt / (beta * gamma));
            std::vector<float> trajectory = {x};
            for(float i = 0 ; i < numSteps ; i++)
            {
                float lamda_old = lamda;
                lamda += u * dt;
                workPerformed += this->U(x, lamda) - this->U(x, lamda_old);
                float randomNormalNumber = distribution(generator);
                x += - (k / gamma) * (x - lamda) * dt + randomNormalNumber * standardDeviation;
                trajectory.push_back(x);
            }

            return std::make_pair(trajectory, workPerformed);
        }
};


int main()
{
    // beta defines the temperature = 1 / (kBT)
    // Can be changed if simulation is needed at higher or lower temperatures
    float k, beta, gamma;
    k = beta = gamma = 1;

    std::ofstream csvfile;
    csvfile.open ("trajectory.csv");

    int numSteps = 100;
    float timeStep = 0.1;
    float totalTime = timeStep * numSteps;
    float lambda = 5;
    BrownianSystem system(k, beta, gamma, lambda / totalTime);
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,1.0);
    float numTrajectories = 100000;

    for(int i = 0 ; i <= numSteps ; i++)
        csvfile << "x_" << i << ",";

    csvfile << "w" << ",";
    csvfile << "isForward" << std::endl;

    // Generating forward trajectories
    for(int trajNo = 0 ; trajNo < numTrajectories ; trajNo++)
    {
        
        float startPoint = (1 / (beta * k)) * distribution(generator);

        std::pair<std::vector<float>, float> p = system.runSimulation(startPoint, 0, numSteps, timeStep);
        for(float x : p.first)
            csvfile << x << ",";
        csvfile << p.second << ",";
        csvfile << 1 << std::endl;
    }

    BrownianSystem system2(k, beta, gamma, -lambda / totalTime);

    // Generating backward trajectories
    for(int trajNo = 0 ; trajNo < numTrajectories ; trajNo++)
    {
        
        float startPoint = (1 / (beta * k)) * distribution(generator);

        std::pair<std::vector<float>, float> p = system2.runSimulation(startPoint, lambda, numSteps, timeStep);
        for(float x : p.first)
            csvfile << x << ",";
        csvfile << p.second << ",";
        csvfile << 0 << std::endl;
    }

    return 0;
}