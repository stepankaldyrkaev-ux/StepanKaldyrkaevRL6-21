#ifndef _double_linked_list_h_
#define _double_linked_list_h_
#include <iostream>
#include <vector>
struct Data {
	std::vector<std::pair<double,double>> pulse;
	double amp;
	Data(std::vector<std::pair<double,double>> dem, double yoo);
	
};

struct Node {
	const Data* cur_pulse;
	Node* next;
	Node* prev;
	int number;
	Node(const Data* d, int num);
};

class DoubleLinkedList {
	private :
		Node* Head;
		Node* Tail;
		int countNodes;
		/*можно добавлять любые функции и переменные*/
	public :
		DoubleLinkedList();
		~DoubleLinkedList();
		
		void push_back(const Data* d);  //добавить узел в конец
		void push_front(const Data* d); //добавить узел в начало
		std::vector<std::pair<double,double>> get_Node(int num_node) const;  //если узла не существует, то вернуть точки последнего импульса при num_node > 0, иначе - первый
																									//функция возвращает точки t,I
		int getCountNodes() const; //получить число импульсов
		void pop_front(); //удалить первый импульс
		void pop_back(); //удалить последний импульс
		void insert(const Data* d, int num_node); //вставить узел в произвольное место списка, если num_node > узлов, то добавить в конец, если num_node < 0, то записать в самое начало	
		double getAm(int numNode) const;
};

class ProcessPulses : public DoubleLinkedList {
	private :
		/*можно добавлять любые функции и переменные*/
		double normalizationCoef; //нормализация импульсов - рекомендую выполнять при добавлении объектов
	public :
		ProcessPulses();
		ProcessPulses(const char* fileName);
		~ProcessPulses();
		std::vector<std::pair<double,double>> getPulse(int numNode, bool normalize = false) const; //получение импульса
		std::vector<std::pair<double,double>> averPulse(int startNode, int countNode) const; //усреднение импульсов
		std::vector<std::pair<double,double>> diffPulse(int numNode) const; //дифференцирование импульса
		double intPulse(int numNode, int start, int end) const; //интегрирование части импульса, если задано отрицательное значение то интегрируется весь импульс
		double getRiseTime(int numNode) const; //длительность нарастающего импульса
		double getFailTime(int numNode) const; //длительность спадающего импульса
		double getAmpl(int numNode) const; //получение амплитуды импульса
		int getCountPulse() const; //получение числа импульсов
		double getDurPulse(int numNode, int start, int end) const; //получение длительности импульса
};

enum SaveTo {
	show = 0,
	png = 1,
	jpeg = 2,
};

class Gnuplot {
	private :
	/*можно добавлять любые функции и переменные*/
	public :
	/*можно добавлять любые функции и переменные*/
	
	void buildPulse(const std::vector<std::pair<double,double>>& pulse, enum SaveTo paramToSave, const char* filename = "Pulse");
};




#endif