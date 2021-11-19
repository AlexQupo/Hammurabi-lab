#include <iostream>
#include <cstdlib>
#include <ctime>


class City {
private:
	int population_ = 100;
	int bushelOfWheat_ = 2800;
	int acresOfLand_ = 1000;
	/*
	 *Начальные значения:
	    В городе проживает 100 человек
	    В закромах города 2800 бушелей пшеницы
	    Город занимает 1000 акров земли
	*/
public:
	int getPopulation() const {
		return population_;
	}

	int getBushelOfWheat() const {
		return bushelOfWheat_;
	}

	int getAcresOfLand() const {
		return acresOfLand_;
	}

	void setPopulation(int value) {
		population_ = value;
	}

	void setBushelOfWheat(int value) {
		bushelOfWheat_ = value;
	}

	void setAcresOfLand(int value) {
		acresOfLand_ = value;
	}

};

class Round {
private:
	int numOfRound_;
	int amountOfDeadPeople_ = 0;
	int amountOfNewPeople_ = 0;
	bool isPlague_ = false;
	int currentPopulation_ = 0;
	int amountOfWheatHarvested_ = 0;
	int amountOfWheatPerAcre_ = 0;
	int amountOfWheatDestroyByRats_ = 0;
	int currentCitySize_ = 0;
	int pricePerAcreOfLandInRound_ = 0;
	City city_;
	int acresOfLandPurchased = 0;
	int acresOfLandSold = 0;
	int c;
	int d;


	void UpdatePrice() {
		int minValue = 17;
		int widthValue = 26 - 17 + 1;
		pricePerAcreOfLandInRound_ = minValue + std::rand() % widthValue;
	}

	int InputOfQuantity(std::string text, int min = 0, int max = INT_MAX) {
		int cost;
		for (;;) {
			std::cout << text << " Максимально значение: "<< max << "\n" << std::flush;
			if ((std::cin >> cost).good() && (min <= cost) && (cost <= max)) return cost;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cout << "Введите количество в целочисленном эквиваленте.\n";
			}
			else {
				std::cout << "Вы ввели отрицательное число или больше, чем имеете.\n";
			}
			std::cin.ignore(100, '\n');
		}
	}

	void RequestInput() {


	}

public:
	void NewGame() {
		city_ = City();
		numOfRound_ = 0;

	}

	void Next() {// Новости, ввод пользователя, подсчет итогов
		numOfRound_++;
		UpdatePrice();
		int maxAvailableNumberOfAcresForPurchase = city_.getBushelOfWheat() / pricePerAcreOfLandInRound_; // доступной земли на покупку
		int maxAvailableNumberOfAcresForSell = city_.getAcresOfLand(); // доступной земли на продажу
		int maxAvailableNumberOfBushelOfWheat = city_.getBushelOfWheat(); // доступные бушелей пшеницы
		float maxAvailableNumberOfSowAcresOfLand = city_.getPopulation() * 10; // максимальное количество посадки акров по числу жителей
		int maxAvailableNumberOfWheatSeeds = (int)maxAvailableNumberOfSowAcresOfLand * .5f; // максимальное число пшеницы для посадки максимального количества посадки акров по числу жителей - доделать
		if(maxAvailableNumberOfWheatSeeds >= city_.getBushelOfWheat()) {//Если требуемое число выше доступного, то берется доступное
			maxAvailableNumberOfWheatSeeds = city_.getBushelOfWheat();
		}
		InputOfQuantity("Сколько акров земли вы хотите купить?", 0, maxAvailableNumberOfAcresForPurchase);
		InputOfQuantity("Сколько акров земли вы хотите продать?", 0, maxAvailableNumberOfAcresForSell);
		InputOfQuantity("Сколько бушелей пшеницы вы хотите использовать в качестве еды?", 0, maxAvailableNumberOfBushelOfWheat);
		InputOfQuantity("Сколько акров земли необходимо засеять пшеницей?", 0, maxAvailableNumberOfWheatSeeds);


	}

	void End() { // Основная логика перед началом следующего раунда
		int wheatConsumption = city_.getBushelOfWheat() - (city_.getPopulation() * 20);
		city_.setBushelOfWheat(wheatConsumption);

	}
};


int main() {
	setlocale(LC_ALL, "Russian");
	Round rnd = Round();
	rnd.Next();

	//srand(time(0));
	/* int minValue = 17;
	 int widthValue = 26 - 17 + 1;
	 int pricePerAcre = 17 + std::rand() % 10;
	 std::cout << pricePerAcre << std::endl;*/
	
}
