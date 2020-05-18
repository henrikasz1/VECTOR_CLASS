//#define pragma once
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

using namespace std;
/*                             IKI V1.0 versijos
struct student{
  string name;//vardas
  string lastName;//pavarde
  int egz;//egzamino rezultatai
  double median;//naudojamas medianos isvedimui
  double average;//naudojamas vidurkio isvedimui
  int m=0; //namu darbu rezultatu kiekis
  vector<int> A; //vektorius, kuriame bus saugojami namu darbu rezultatai
};//struktura

#endif // STRUCT_H_INCLUDED
*/
class person {  //abstract class
protected:
    string name; //vardas
    string lastName; //pavarde
public:
    //setters
    inline void setName (string name) {this->name=name;}
    inline void setLastName (string lastName) {this->lastName=lastName;}
    //getters
    inline string getName() const {return name;}
    inline string getLastName() const {return lastName;}

    virtual void calculations() = 0;//using calculations method to show how virtual functions work
};
class student: public person {                         //struct to class to conform V1.1 version
private:
    //string name;//vardas
    //string lastName;//pavarde
    int egz;//egzamino rezultatas
    double median;
    double finalMedian;
    double average;
    double finalAverage;
    vector<int> A; //namu darbu rezultatai
public:
   //student() : egz(0), median(0.0), average(0.0), finalAverage(0.0), finalMedian(0.0) {}   //default constructor
    student(){
        name = " ";
        lastName = " ";
        egz=0;
        median = 0.0;
        finalAverage = 0.0;
        finalMedian = 0.0;;
    }
    //adding copy semantics - kopijavimo semantika nera reikalinga siame kode, nes klase neturi jokiu pointeriu
    //copy constructor
    student (const student& z){//kai naudojama pvz.:      student B = A;
        name =  z.name;
        lastName = z.lastName;
        egz = z.egz;
        median = z.median;
        finalAverage = z.finalAverage;
        finalMedian = z.finalMedian;
        A = z.A;
    }
    //assignment operator
    student& operator = (const student &other)// kai naudojama pvz.:    A = B;
    {
        if(&other == this){return *this;}
        name =  other.name;
        lastName = other.name;
        egz = other.egz;
        median = other.median;
        finalAverage = other.finalAverage;
        finalMedian = other.finalMedian;
        return *this;
    }
   ~student() {}
    //getters
    inline double getMedian() const {return finalMedian;}
    inline double getAverage() const {return finalAverage;}
    inline int getEgz() const {return egz;}
    //setters
    inline void setEgz (int egz) {this->egz = egz;}
    inline void setHW (vector<int> X) { A=X;}
    //operators
    friend ostream& operator<<(ostream& out, vector<student>&vect) { //isvedimo operatorius
        for (vector<student>::iterator i = vect.begin(); i != vect.end(); ++i)
        {
            out.width(15);
            out << left << (*i).name;
            out.width(15);
            out << left << (*i).lastName;
            out.width(15);
            out << left << fixed << setprecision(2) << (*i).finalMedian;
            out.width(15);
            out << left << setprecision(2) << (*i).finalAverage << endl;
        }
        return out;
    }
    friend istream& operator>>(istream& in, student &vect) { //ivedimo operatorius(naudoju tik vardui ir pavardei ivesti)

        in >> vect.name >> vect.lastName;
        return in;
    }
    friend bool operator<(const student &A, int n) // operatorius, kuris bus naudojamas vektoriaus paskirstymui
    {
        return (A.finalAverage < n);
    }
    //paskutiniai trys operatoriai panaudojami if salygoje, kuri isveda i console mokinius pagal tam tikra seka -> functions.cpp 45 eilute
    friend bool operator>(const student &a, const student &b)
    {
        return (a.name > b.name);
    }
    friend bool operator==(const student &a, const student &b)
    {
        return (a.name==b.name);
    }
    friend bool operator<(const student &a, const student &b)
    {
        return (a.lastName<b.lastName);
    }
    //methods
    void calculations() override; //override zodis nera privalomas, bet taip patogiau skaityti koda
};

#endif // STRUCT_H_INCLUDED
