#include <iostream>
#include "double_linked_list.h"
#include <vector>
#include <utility>
#include <fstream>
#include <string.h>
#include <cstdio>
Data::Data(std::vector<std::pair<double,double>> dem, double yoo){
	pulse = dem;
	amp = yoo;
}
Node::Node(const Data* d, int num){
	cur_pulse = d;
	next = nullptr;
	prev = nullptr;
	number = num;
}
DoubleLinkedList::DoubleLinkedList(){
	Head = nullptr;
	Tail = nullptr;
	countNodes = 0;
}
DoubleLinkedList::~DoubleLinkedList(){
	Node* current = Head;
    while (current) {
        Node* next = current->next;
        delete current->cur_pulse;
        delete current;
        current = next;
    }
	Head = nullptr;
	Tail = nullptr;
	countNodes = 0;
}
void DoubleLinkedList::push_back(const Data* d){
	Node* p = new Node(d,countNodes);
    if (Head==nullptr) {
		Head = p;
		Tail = p;
		return;
	}
	Tail->next = p;
	Node* t = Tail;
	Tail = p;
	p->prev = t;
	countNodes++;
}
void DoubleLinkedList::push_front(const Data* d){
	Node* p = new Node(d,countNodes);
	if (Head==nullptr) {
		Head = p;
		Tail = p;
		return;
	}
	Head->prev = p;
	Node* t = Head;
	Head = p;
	Head->next = t;
	countNodes++;
}
void DoubleLinkedList::pop_front(){
	if (Head==nullptr) return;
	Node* p = Head;
	Head = p->next;
	Head->prev = nullptr;
	countNodes--;
	delete p;
}
void DoubleLinkedList::pop_back(){
	if (Head==nullptr) return;
	if (Head == Tail) {
		pop_front();
		return;
	}
	Node* p = Tail->prev;
	p->next = nullptr;
	delete Tail;
	Tail = p;
}
std::vector<std::pair<double,double>> DoubleLinkedList::get_Node(int num_node) const{
	const Data* d;
	if(num_node<0){
		Node* p = Head;
		d = p->cur_pulse;
		return d->pulse;
	}
	if(num_node>countNodes-1){
		Node* p = Tail;
		d = p->cur_pulse;
		return d->pulse;
	}
	Node* p = Head;
	while (p && p->number != num_node){
		 p = p->next;
	}
	d = p->cur_pulse;
	return d->pulse;
}
int DoubleLinkedList::getCountNodes() const{
	return countNodes;
}
void DoubleLinkedList::insert(const Data* d, int num_node){
	Node* p = new Node(d,num_node);
	if ((Head==nullptr)&&(num_node==0)) {
		Head = p;
		Tail = p;
		return;
	}
	if(num_node<0){
		this->push_front(d);
		return;
	}
	if(num_node>countNodes){
		this->push_back(d);
		return;
	}
	Node* cur = Head;
	while (cur && cur->number != num_node-1){
		 cur = cur->next;
	}
	Node* buf = cur->next;
	buf->prev = p;
	p->next = buf;
	cur->next = p;
	p->prev = cur;
	while (buf && buf!= Tail){
		 buf->number++;
		 buf = buf->next;
	}
	buf->number++;
	countNodes++;
}
ProcessPulses::ProcessPulses(const char* fileName):DoubleLinkedList(){
	std::ifstream file(fileName, std::ios::binary | std::ios::ate);
	long int size = file.tellg();
	file.seekg(0, std::ios::beg);
    unsigned char byte;
	unsigned char* buf = new unsigned char[size];
	long int ind = 0;
    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        buf[ind] = byte;
		ind++;
    }
	if (!file.eof()) {
        std::cerr << "Ошибка при чтении файла " << std::endl;
    }
    file.close();
	std::vector<double> buf1;
	buf1.reserve(size/2);
	unsigned char low, high;
	ind = 0;
	double time = 0;
	bool null = false;
	bool arg = false;
	double coef = 0;
	double max = 0;
	std::vector<std::pair<double,double>> pulse;
	pulse.reserve(size/2);
	for(int i=2;i<size-1;i=i + 4){
		low = buf[i];
		high = buf[i+1];
		buf1[ind] = double((high<<8)|low);
		null = (buf1[ind] == 0? true : false);
		if(!null){
			if(buf1[ind-1]	==0){
				pulse.push_back(std::pair<double, double>(0, 0));
				time+=0.001;
			}
			pulse.push_back(std::pair<double, double>(time, buf1[ind]));
			max = (buf1[ind]>max? buf1[ind]:max);
			time+=0.001;
		}
		if(null&&(i!=2)&&(buf1[ind-1]!=0)){
			pulse.push_back(std::pair<double, double>(time, 0));
			Data* dat = new Data(pulse, max);
			coef = (max>coef? max:coef);
			max = 0;
			this->push_back(dat);
			pulse.clear();
			time = 0;
		}
		ind++;
	}
	normalizationCoef = coef;
	delete[] buf;
}
ProcessPulses::~ProcessPulses(){
	normalizationCoef = 0;
}
std::vector<std::pair<double,double>> ProcessPulses::getPulse(int numNode, bool normalize) const{
	std::vector<std::pair<double,double>> pulse = this->get_Node(numNode);
	if(normalize){
		const int size = pulse.size();
		std::vector<std::pair<double,double>> result;
		for (int i = 0; i < size; i++) {
			result.push_back(std::pair<double, double>(pulse[i].first, (pulse[i].second)/normalizationCoef));
		}
		return result;
	}
	return pulse;
}
std::vector<std::pair<double,double>> ProcessPulses::diffPulse(int numNode) const{
	std::vector<std::pair<double,double>> pulse = this->get_Node(numNode);
	std::vector<std::pair<double,double>> diff;
	const int size = pulse.size();
	for (int i = 0; i < size-1; i++) {
        diff.push_back(std::pair<double, double>(pulse[i].first, (pulse[i+1].second - pulse[i].second)/(0.001)));
    }	
	diff.push_back(std::pair<double, double>(pulse[size-1].first, pulse[size-2].second));
	return diff;
}
std::vector<std::pair<double,double>> ProcessPulses::averPulse(int startNode, int countNode) const{
	std::vector<std::pair<double,double>> result;
	std::vector<int> count;
	for(int i=startNode; i<startNode+countNode; i++){
		std::vector<std::pair<double,double>> pulse = this->get_Node(i);
		for(int j = 0; j<result.size(); j++){
			result[j].second+=pulse[j].second;
			count[j]++;
		}
		int size = result.size();
		for(int k = size; k<pulse.size(); k++){
			result.push_back(std::pair<double, double>(pulse[k].first, pulse[k].second));
			count.push_back(1);
		}
	}
	for(int j = 0; j<result.size(); j++){
		result[j].second=result[j].second/(double)count[j];
	}
	return result;
}
double ProcessPulses::intPulse(int numNode, int start, int end) const{
	std::vector<std::pair<double,double>> pulse = this->get_Node(numNode);
	int i=0;
	double result = 0;
	bool getAm = true;
	double Amp = this->getAmpl(numNode);
	if((start<0)||(end<0)){
		start = 0;
		end = 0;
	}
	double st = (double(start)/100)*(Amp);
	double en = (double(end)/100)*(Amp);
	while(pulse[i].second<=st){
		i++;
	}
	for(int j = i;((getAm||(pulse[j].second>=en))&&(j<pulse.size())); j++ ){
		result+=pulse[j].second*(0.001);
		if(getAm&&(pulse[j].second==Amp))
			getAm = false;
	}
	return result;
}
double ProcessPulses::getRiseTime(int numNode) const{
	std::vector<std::pair<double,double>> diff = this->diffPulse(numNode);
	int i = 0;
	while(diff[i].second+5000>0){
		i++;
	}
	return(diff[i].first);
}
double ProcessPulses::getFailTime(int numNode) const{
	std::vector<std::pair<double,double>> diff = this->diffPulse(numNode);
	int i = diff.size()-3;
	double time1, time2;
	while(diff[i].second+8000>0){
		i--;
	}
	time2=diff[i].first;
	while(diff[i].second<=0){
		i--;
	}
	time1=diff[i].first;
	return(time2-time1);
}
double DoubleLinkedList::getAm(int num_node) const{
	const Data* d;
	if(num_node<0){
		Node* p = Head;
		d = p->cur_pulse;
		return d->amp;
	}
	if(num_node>countNodes-1){
		Node* p = Tail;
		d = p->cur_pulse;
		return d->amp;
	}
	Node* p = Head;
	while (p && p->number != num_node){
		 p = p->next;
	}
	d = p->cur_pulse;
	return d->amp;
}
double ProcessPulses::getAmpl(int numNode) const{
	double Ampl = this->getAm(numNode);
	return Ampl;
}
int ProcessPulses::getCountPulse() const{
	int kol = this->getCountNodes();
	return kol;
}
double ProcessPulses::getDurPulse(int numNode, int start, int end) const{
	std::vector<std::pair<double,double>> pulse = this->get_Node(numNode);
	int i=0;
	double result = 0;
	bool getAm = true;
	double Amp = this->getAmpl(numNode);
	if((start<0)||(end<0)){
		start = 0;
		end = 0;
	}
	double st = (double(start)/100)*(Amp);
	double en = (double(end)/100)*(Amp);
	while(pulse[i].second<=st)
		i++;
	double time_start = pulse[i].first;
	while((getAm||(pulse[i].second>=en))&&(i<pulse.size())){
		i++;
		if(getAm&&(pulse[i].second==Amp))
			getAm = false;
	}
	double time_end = pulse[i].first;
	return (time_end-time_start);
}
void Gnuplot::buildPulse(const std::vector<std::pair<double,double>>& pulse, enum SaveTo paramToSave, const char* filename){
    FILE* file = fopen("test.dat", "w");
	char PngOutput[100];
	sprintf(PngOutput, "set output '%s.png'\n", filename);
	char JpegOutput[100];
	sprintf(JpegOutput, "set output '%s.jpg'\n", filename);
	const int size = pulse.size();
    for (int i = 0; i < size; i++) {
        double t = pulse[i].first;
        double q = pulse[i].second;
        fprintf(file, "%f\t%f\n", t, q);
    }
    fclose(file);
	FILE* script = fopen("plot.gp", "w");
    fprintf(script, "set terminal %s\n",(paramToSave==show? "wxt" : (paramToSave==png? "png size 1024,768" : "jpeg size 1024,768")));
    fprintf(script, "set title '%s'\n", filename);
	fprintf(script, "%s",(paramToSave==show? "" : (paramToSave==png? PngOutput : JpegOutput)));
    fprintf(script, "plot 'test.dat' using 1:2 with lines\n");
    fprintf(script, "pause -1 '%sPress enter to continue'\n", (paramToSave!=show? "Saved to file, " : ""));
    fclose(script);
    system("gnuplot plot.gp");
}
