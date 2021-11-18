#include <iostream>
#include <cstdlib>
#include <ctime>


class City {
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
};

class Round {
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

	void updatePrice() {
		int minValue = 17;
		int widthValue = 26 - 17 + 1;
		pricePerAcreOfLandInRound_ = minValue + std::rand() % widthValue;
	}

	int inputOfQuantity(std::string text, int min = 0, int max = INT_MAX) {
		int cost;
		for (;;) {
			std::cout << text << "\n" << std::flush;
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

	void requestInput() {


	}

public:
	void reset() {

	}

	void next() {
		updatePrice();
		inputOfQuantity("Сколько акров земли вы хотите купить?", 0, 100);
		inputOfQuantity("Сколько акров земли вы хотите продать?", 0, 100);
		inputOfQuantity("Сколько бушелей пшеницы вы хотите использовать в качестве еды?", 0, 100);
		inputOfQuantity("Сколько акров земли необходимо засеять пшеницей?", 0, 100);
	}

	void end() {

	}
};


int main() {
	setlocale(LC_ALL, "Russian");
	Round rnd = Round();
	rnd.next();
	//srand(time(0));
	/* int minValue = 17;
	 int widthValue = 26 - 17 + 1;
	 int pricePerAcre = 17 + std::rand() % 10;
	 std::cout << pricePerAcre << std::endl;*/

}
