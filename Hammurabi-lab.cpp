#include <iostream>
#include <cstdlib>
#include <ctime>
#include "windows.h"
//#include <math.h>


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
		if (value < 0) {
			value = 0;
		}
		population_ = value;
	}

	void setBushelOfWheat(int value) {
		if (value < 0) {
			value = 0;
		}
		bushelOfWheat_ = value;
	}

	void setAcresOfLand(int value) {
		if (value < 0) {
			value = 0;
		}
		acresOfLand_ = value;
	}

};

class Round {
private:
	// Видимые данные для игрока
	int numOfRound_;//Номер раунда
	int amountOfDeadPeople_ = 0;//Умерло
	int amountOfNewPeople_ = 0;//Приезжих
	bool isPlague_ = false;//Чума
	int currentPopulation_ = 0;//Текущее население
	int amountOfWheatHarvested_ = 0;//Собрано пшеницы +
	int avgAmountOfWheatPerAcre_ = 0;//Получено за Акр
	int amountOfWheatDestroyByRats_ = 0;//Съедино крысами +
	int currentCitySize_ = 0;//Площадь города
	int pricePerAcreOfLandInRound_ = 0;//Цена акра земли в текущем году
	//Скрытые данные
	City city_;
	int currentbushelOfWheat = 0;
	int acresOfLandPurchased = 0;// Земли куплено
	int acresOfLandSold = 0;// Земли продано
	int wheatForFood = 0;// Количество пшеницы на еду
	int landForSowing = 0;// Количество пшеницы на посадку


	void UpdatePrice() {
		int minValue = 17;
		int widthValue = 26 - 17 + 1;
		pricePerAcreOfLandInRound_ = minValue + std::rand() % widthValue;
	}
	int SetRandomValueInRange(int minValue, int widthValue) {
		return minValue + std::rand() % widthValue;
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
		currentPopulation_ = city_.getPopulation();
		currentCitySize_ = city_.getAcresOfLand();
		currentbushelOfWheat = city_.getBushelOfWheat();

		std::cout << "Добро пожаловать в игру Хаммурапи!" << std::endl;
		std::cout << "Вы начинаете игру с:" << std::endl;
		std::cout << "Население: " << city_.getPopulation() << std::endl;
		std::cout << "Бушелей пшеницы: " << city_.getBushelOfWheat() << std::endl;
		std::cout << "Акров земли: " << city_.getAcresOfLand() << std::endl;

		Sleep(3000);

		std::cout << "Да начнется игра!" << std::endl;

	}
	void StartGame() {

		Sleep(3000);
		Next();
	}

	void Next() {// Новости, ввод пользователя, подсчет итогов
		numOfRound_++;
		UpdatePrice();





		int maxAvailableNumberOfAcresForPurchase = city_.getBushelOfWheat() / pricePerAcreOfLandInRound_; // доступной земли на покупку
		int maxAvailableNumberOfAcresForSell = city_.getAcresOfLand(); // доступной земли на продажу
		int maxAvailableNumberOfBushelOfWheat = city_.getBushelOfWheat(); // доступные бушелей пшеницы
		float maxAvailableNumberOfSowAcresOfLand = static_cast<float>(city_.getPopulation()) * 10; // максимальное количество посадки акров по числу жителей
		int maxAvailableNumberOfWheatSeeds = static_cast<int>(maxAvailableNumberOfSowAcresOfLand * .5f); // максимальное число пшеницы для посадки максимального количества посадки акров по числу жителей - доделать
		if (maxAvailableNumberOfWheatSeeds >= city_.getBushelOfWheat()) {//Если требуемое число выше доступного, то берется доступное
			maxAvailableNumberOfWheatSeeds = city_.getBushelOfWheat();
		}
		acresOfLandPurchased = InputOfQuantity("Сколько акров земли вы хотите купить?", 0, maxAvailableNumberOfAcresForPurchase);
		acresOfLandSold = InputOfQuantity("Сколько акров земли вы хотите продать?", 0, maxAvailableNumberOfAcresForSell);
		wheatForFood = InputOfQuantity("Сколько бушелей пшеницы вы хотите использовать в качестве еды?", 0, maxAvailableNumberOfBushelOfWheat);
		landForSowing = InputOfQuantity("Сколько акров земли необходимо засеять пшеницей?", 0, maxAvailableNumberOfWheatSeeds);


	}

	void End() { // Основная логика перед началом следующего раунда
		//int wheatConsumption = city_.getBushelOfWheat() - (city_.getPopulation() * 20);
		//city_.setBushelOfWheat(wheatConsumption);

		//Пшеницы собрано
		amountOfWheatHarvested_ = 0;
		/*avgAmountOfWheatPerAcre_ = 0;
		for (int i = 0; i<=landForSowing; i++) {
			amountOfWheatHarvested_ += SetRandomValueInRange(1, 6);
		}
		avgAmountOfWheatPerAcre_ = amountOfWheatHarvested_ / landForSowing;*/
		avgAmountOfWheatPerAcre_ = SetRandomValueInRange(1, 6);
		amountOfWheatHarvested_ = landForSowing * avgAmountOfWheatPerAcre_;
		city_.setBushelOfWheat(city_.getBushelOfWheat() + amountOfWheatHarvested_);

		//Поело крысами
		float endNumberForRandom = 0.07f * static_cast<float>(city_.getBushelOfWheat());
		endNumberForRandom = std::round(endNumberForRandom);
		amountOfWheatDestroyByRats_ = SetRandomValueInRange(0, static_cast<int>(endNumberForRandom));
		city_.setBushelOfWheat(city_.getBushelOfWheat() - amountOfWheatDestroyByRats_);

		//Потребили жители, умерло - fix
		int tempPopulation = city_.getPopulation();
		city_.setBushelOfWheat(city_.getBushelOfWheat() - wheatForFood);
		int providesResidents = wheatForFood / 20;
		if (providesResidents < city_.getPopulation()) {
			amountOfDeadPeople_ = city_.getPopulation() - providesResidents;
		}
		else {
			amountOfDeadPeople_ = 0;
		}

		//Подсчет населения
		float coefficientOfDead = static_cast<float>(amountOfDeadPeople_) / static_cast<float>(tempPopulation);
		if (coefficientOfDead >= 0.45f) {
			Defeat();
		}

		//Приезжих
		amountOfNewPeople_ = amountOfDeadPeople_ / 2 + (5 - avgAmountOfWheatPerAcre_) * city_.getBushelOfWheat() / 600 + 1;
		if (amountOfNewPeople_ < 0) {
			amountOfNewPeople_ = 0;
		}
		else if (amountOfNewPeople_ > 50) {
			amountOfNewPeople_ = 50;
		}
		city_.setPopulation(city_.getPopulation() + amountOfNewPeople_);

		//Чума 12% = 3/25 12/100
		int dice = SetRandomValueInRange(1, 100);
		if (dice <= 12) {
			isPlague_ = true;
			city_.setPopulation(city_.getPopulation() / 2);
		}
		else {
			isPlague_ = false;
		}
	}

	void Defeat() {
		std::cout << "Вы проиграли!" << std::endl;
	}
};


class Game {

	void Start() {
		
	}

	void Save() {
		
	}

	void Resume() {
		
	}

	void Stop() {
		
	}

};


int main() {
	setlocale(LC_ALL, "Russian");
	Round rnd = Round();
	rnd.NewGame();
	rnd.Next();

	//srand(time(0));
	/* int minValue = 17;
	 int widthValue = 26 - 17 + 1;
	 int pricePerAcre = 17 + std::rand() % 10;
	 std::cout << pricePerAcre << std::endl;*/
	
}
