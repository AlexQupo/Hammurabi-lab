#include <iostream>

class City
{
protected:
    int population_ = 100;
    int bushelOfWheat_ = 2800;
    int acresOfLand_ = 1000;
/*
 *Начальные значения:
    В городе проживает 100 человек
    В закромах города 2800 бушелей пшеницы
    Город занимает 1000 акров земли
*/
};
class Round
{
protected:
    int numOfRound_;
    int amountOfDeadPeople_;
    int amountOfNewPeople_;
    bool isPlague_;
    int currentPopulation_;
    int amountOfWheatHarvested_;
    int amountOfWheatPerAcre_;
    int amountOfWheatDestroyByRats_;
    int currentCitySize_;
    int pricePerAcreOfLandInRound_;

};

int main()
{
    std::cout << "Hello World!\n";
}
