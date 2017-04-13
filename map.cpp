#include "iostream"
#include <limits>

using namespace std;


template < typename key,
           typename t >
class mapPtr{
private:
	bool up;
	key k;
	t data;
	mapPtr<key, t>* nxt;
	mapPtr<key, t>* prv;
public:
	key getKey();
	t getData();
	bool more(key);
	void addBefore(key, t);
	void addAfter(key, t);
	bool equalKey(key);
	bool hasNext(bool);
	bool hasNext();
	void setUp(bool);
	mapPtr<key, t>* getPrev();
	mapPtr<key, t>* getNext();
	mapPtr<key, t>* getNext(bool);
	void setPrev(mapPtr<key, t>*);
	void setNext(mapPtr<key, t>*);
	void init(key, t);
	void init(key, t, mapPtr<key, t>*, mapPtr<key, t>*);
	mapPtr();
	mapPtr(key, t, mapPtr<key, t>*, mapPtr<key, t>*);
	void dlt();
};

template<typename key, typename t>
key mapPtr<key, t>::getKey(){
	return k;
}

template<typename key, typename t>
t mapPtr<key, t>::getData(){
	return data;
}

template<typename key, typename t>
void mapPtr<key, t>::addBefore(key k_, t data_){
	if(prv != NULL){
		cout << "NULLLL";
		mapPtr<key, t>* tmp = prv;
		prv = new mapPtr(k_, data_, this, tmp);
		tmp -> setNext(prv);
	}else prv = new mapPtr(k_, data_, this, NULL);
}

template<typename key, typename t>
void mapPtr<key, t>::addAfter(key k_, t data_){
	if(nxt != NULL){
		mapPtr<key, t>* tmp = nxt;
		nxt = new mapPtr(k_, data_, tmp, this);
		tmp -> setPrev(nxt);
	}else nxt = new mapPtr(k_, data_, NULL, this);
}

template<typename key, typename t>
bool mapPtr<key, t>::more(key k_){
	return k > k_;
}

template<typename key, typename t>
bool mapPtr<key, t>::equalKey(key k_){
	return k == k_;
}

template<typename key, typename t>
bool mapPtr<key, t>::hasNext(bool up_){
	if(getNext(up_) != NULL)
		return true;
	return false;
}

template<typename key, typename t>
bool mapPtr<key, t>::hasNext(){
	if(getNext() != NULL)
		return true;
	return false;
}

template<typename key, typename t>
void mapPtr<key, t>::setUp(bool up_){
	up = up_;
}

template<typename key, typename t>
mapPtr<key, t>* mapPtr<key, t>::getNext(bool up_){
	if(up_) return nxt;
	prv -> setUp(up);
	return prv;
}

template<typename key, typename t>
mapPtr<key, t>* mapPtr<key, t>::getPrev(){
	return prv;
}


template<typename key, typename t>
mapPtr<key, t>* mapPtr<key, t>::getNext(){
	if(up) return nxt;
	prv -> setUp(up);
	up = false;
	return prv;
}


template<typename key, typename t>
void mapPtr<key, t>::setPrev(mapPtr<key, t>* prev){
	prv = prev;
}



template<typename key, typename t>
void mapPtr<key, t>::setNext(mapPtr<key, t>* next){
	nxt = next;
}

template<typename key, typename t>
mapPtr<key, t>::mapPtr(){
	nxt = NULL;
	prv = NULL;
	up = true;
	k = 0;
	data = 0;
}

template<typename key, typename t>
void mapPtr<key, t>::init(key k_, t data_){
	k = k_;
	data = data_;
	nxt = NULL;
	prv = NULL;
	up = true;
}

template<typename key, typename t>
mapPtr<key, t>::mapPtr(key k_, t data_, mapPtr<key, t>* next, mapPtr<key, t>* prev){
	k = k_;
	data = data_;
	nxt = next; 
	prv = prev;
	up = true;
}

template<typename key, typename t>
void mapPtr<key, t>::init(key k_, t data_, mapPtr<key, t>* next, mapPtr<key, t>* prev){
	k = k_;
	data = data_;
	nxt = next; 
	prv = prev;
	up = true;
}

template<typename key, typename t>
void mapPtr<key, t>::dlt(){
	if(nxt != NULL)
		if(prv != NULL){
			nxt -> setPrev(prv);
			prv -> setNext(nxt);
		}else{
			nxt -> setPrev(NULL);	
		}
	else{
		if(prv != NULL)
			prv -> setNext(NULL);
	}
}

template < typename key,
           typename t >
class Map{
private:
    mapPtr<key, t>* head;
    int count;
    int maxSize;
public:
	bool empty();
	int size();
	int max_size();
	bool erase(key);
	mapPtr<key, t>* begin();
	mapPtr<key, t>* rbegin();
	mapPtr<key, t>* end();
	void updateHead();
	mapPtr<key, t>* getLast();
	mapPtr<key, t>* findPlace(key);
    Map();
    void show();
    void clear(){ count = 0;};
    bool add(key, t);
    bool contain(key);
};


template<typename key, typename t>
bool Map<key, t>::erase(key k_){
	mapPtr<key, t>* tmp =  findPlace(k_);
	if(tmp->getPrev()!=NULL)
		tmp->getPrev()->dlt();
	return true;
}

template<typename key, typename t>
bool Map<key, t>::empty(){
	return count()==0;
}

template<typename key, typename t>
int Map<key, t>::max_size(){
	return 32767;
}

template<typename key, typename t>
int Map<key, t>::size(){
	return count;
}

template<typename key, typename t>
mapPtr<key, t>* Map<key, t>::end(){
	return getLast();
}

template<typename key, typename t>
mapPtr<key, t>* Map<key, t>::begin(){
	return head;
}

template<typename key, typename t>
mapPtr<key, t>* Map<key, t>::rbegin(){
	mapPtr<key, t> tmp = getLast();
	tmp -> setUp(false);
	return tmp;
}

template<typename key, typename t>
void Map<key, t>::updateHead(){
	if(head)
		return;
	while(head->getPrev() != NULL){
		head = head->getPrev();
	}
}

template<typename key, typename t>
mapPtr<key, t>* Map<key, t>::getLast(){
	mapPtr<key, t>* tmp = head;
	if(head == NULL)
		return NULL;
	while(tmp->hasNext()){
		tmp = tmp -> getNext();
	}
	return tmp;
}

template<typename key, typename t>
mapPtr<key, t>* Map<key, t>::findPlace(key k_){
	if(head == NULL)
		return NULL;
	mapPtr<key, t>* tmp = head;
	do{
		if(!(tmp -> more(k_)))
			return tmp;

		tmp = tmp->getNext();
	}while(tmp != NULL);
	return getLast();
}

template<typename key, typename t>
bool Map<key, t>::contain(key k_){
	mapPtr<key, t>* tmp = new mapPtr<key, t>;
	tmp = head;
	if(head == NULL)
		return false;
	do{
		if(tmp -> equalKey(k_))
			return true;
		tmp = tmp->getNext();
	}
	while(tmp != NULL);
	return false;
};



template<typename key, typename t>
void Map<key, t>::show(){
	if(head == NULL)
		return;
	mapPtr<key, t>* tmp = head;
	do{
		cout << tmp -> getKey() << " " << tmp -> getData() << endl;
		tmp = tmp -> getNext();
	}
	while(tmp != NULL);
    for(int i = 0; i < count; i++);
      //  cout << " " << data[i] << endl;
};

template<typename key, typename t>
bool Map<key, t>::add(key k_, t data_){
	if((contain(k_)))
		return false;
	mapPtr<key, t>* tmp = findPlace(k_);
	if(tmp == NULL)
		head = new mapPtr<key, t>(k_, data_, NULL, NULL);
	else{
		tmp -> addBefore(k_, data_);
		updateHead();	
	}
	count++;
    return true;
};

template<typename key, typename t>
Map<key, t>::Map(){
	head = NULL;
    count = 0;
}

int main(){
    Map <int,double>
            mp;
    mp.add(3, 2.2);
	mp.show();
    return 0;
}
