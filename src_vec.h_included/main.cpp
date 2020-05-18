#include "functions.h"
#include "struct.h"

int main ()
{

  //srand(time(0));   unsafe
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1,10);

  vector<student> B;//vektorius, kuriame bus kiekvieno mokinio duomenys
  //-----
  char check; //elementas, kuris tikrina, ar norima ivesti dar viena mokini
  char choice; // elementas, kuris tikrina, kokiu budu ivesti namu darbu rezultatus
  char read; //elementas, kuris tikrina, ar duomenys bus nuskaityti is failo, ar ivesti per console

  vector<student> M; //i si vektoriu nuskaitys sugeneruota faila
  vector<student> kvaili; //v1.0 versijai

  vector<int> laikinas;
  int n=0;//vektoriaus dydis

  string vardas;
  int exam;
  //nuskaitymas
  cout << "Ar norite ivesti duomenis, ar, kad juos nuskaitytu is failo? \n Ivesti - spauskite 1 \n Nuskaityti is Random Failu(v0.4) - spauskite 2 \n Nuskaityti is failo - iveskite bet koki kita elementa \n";
  cin >> read;
  if (read=='1')
  {
        do //jeigu 1, ciklas kartojamas, jeigu ivedamas kitas skaicius, ciklas baigiasi, jeigu cin.fail(), ciklas taip pat baigiasi
        {
          B.push_back(student());
          cout << "Iveskite mokinio varda\n";
          cin >> vardas;
          B[n].setName(vardas);
          //cin >> B[n].name;
          for (int p=0; p<B[n].getName().length(); p++)
          {
            while(!isalpha(B[n].getName()[p]))
            {
                cout << "Ivedete netinkama reiksme, bandykite dar karta \n";
                cin.clear();
                cin >> vardas;
                B[n].setName(vardas);
                //cin >> B[n].name;
            }
          }
          cout << "Iveskite mokinio pavarde \n";
          cin >> vardas;
          B[n].setLastName(vardas);
          //cin >> B[n].lastName;
          for (int b=0; b<B[n].getLastName().length(); b++)
          {
            while(!isalpha(B[n].getLastName()[b]))
            {
                cout << "Ivedete netinkama reiksme, bandykite dar karta \n";
                cin.clear();
                cin >> vardas;
                B[n].setLastName(vardas);
                //cin >> B[n].lastName;
            }
          }

          //-----------------
          cout << "Ar norite, kad pazymius: \nSugeneruotu automatiskai? - iveskite bet koki kita elementa \n Suvestumete patys? - iveskite 1\n";
          cin >> choice;
          int more=1;
          int input; //input'as vektoriui
          if (choice=='1')
          {
            while(more==1)
            {
              cout << "Iveskite pazymi \n";
              cin >> input;
              laikinas.push_back(input);
              //B[n].A.push_back(input);
              while (input<0 || input>10 ||cin.fail())
              {
                //B[n].A.pop_back();
                laikinas.pop_back();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ivedete netinkama reiksme \n";
                cin >> input;
                //B[n].A.push_back(input);
                laikinas.push_back(input);
              }
              B[n].setHW(laikinas);
              cout << "Ar norite ivesti dar viena pazymi?\n Jei taip - spauskite 1 \n Jei ne - iveskite bet koki kita elementa \n";
              cin >> more;
            }
          }
          else
          {
              int random=dist(mt);
              for (int j=0; j<random; j++)
              {
                laikinas.push_back(dist(mt));
                //B[n].A.push_back(rand()%10+1);
              }
              B[n].setHW(laikinas);
          }

          //-------------
          cout << "Iveskite mokinio egzamino rezultata \n";
          cin >> exam;
          B[n].setEgz(exam);
          //cin >> B[n].egz;
          while(cin.fail() || B[n].getEgz()<0 || B[n].getEgz()>10)
          {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Egzamino rezultatas gali buti sudarytas tik is skaiciu, bandykite dar karta \n";
            //cin >> B[n].egz;
            cin >> exam;
            B[n].setEgz(exam);
          }
          n++;
          cout << "Ar norite ivesti dar vieno mokinio duomenis? \n Jei taip, spauskite 1 \n Jei ne, iveskite bet koki kita elementa \n";
          cin >> check;
        }while(check=='1');

        //isvedimas
      /*  for (int e=0; e<n; e++)
        {
        B[e].median=0.4*median(B[e].A)+0.6*B[e].egz;
        }
        for (int e=0; e<n; e++)
        {
        B[e].average=0.4*average(B[e].A)+0.6*B[e].egz;
        }*/
        calculate(B);
        output (n, B);//isvedimo funkcija


    laikinas.clear();
 }
 else if (read=='2')
 {
    auto start = std::chrono::steady_clock::now();
    int howMany;//pazymiu kiekis
    int numOfStudents=1000;
    string nameOfFile=" ";
    cout << "Iveskite, kiek norite, kad sugeneruotu pazymiu \n";
    cin >> howMany;
    for (int i=0; i<5; i++)
    {
       auto start = std::chrono::steady_clock::now();
       cout << "Failo dydis: " << numOfStudents << endl;
       generateFile(numOfStudents, howMany, nameOfFile);
       readFile(M, nameOfFile);
       //M.shrink_to_fit();
       distributeFile(numOfStudents, M, kvaili);
       M.clear();
       kvaili.clear();
       numOfStudents*=10;//dauginu is 10, kad generuotu failus su vis didesniais studentu kiekiais, kaip ir praso uzduotis
       auto finish = std::chrono::steady_clock::now();
       cout << "Bendras laikas: " << std::chrono::duration <double, milli>(finish - start).count() << "ms" << endl << endl;
    }
 }
 else
 {
    try
    {
    ifstream in ("kursiokai.txt");
    if (!in.good())
    {
      throw runtime_error("failas neegzistuoja \n");
    }
    int nd;//kintamasis, kuriuo nuskaitysiu visus skaicius
    string line; //kintamasis, kuriuo nuskaitysiu visa eilute
        while (getline(in, line))//kol galima paimti eilute, tol nuskaitines
        {
          istringstream enter(line);//kadangi getline() paima duomenis stringo formatu, naudoju istringstream, kad extractint elementus
          B.push_back(student());
          //enter >> B[n].name;
          enter >> vardas;
          B[n].setName(vardas);
          //enter >> B[n].lastName;
          enter >> vardas;
          B[n].setLastName(vardas);
          while(enter)
          {
            enter >> nd;
            laikinas.push_back(nd);
            //B[n].A.push_back(nd);
          }
          B[n].setEgz(laikinas.back());
          laikinas.pop_back();
          B[n].setHW(laikinas);
          n++;
        }
        in.close();
    }
    catch(exception &e)
    {
      system("cls");
      cout << e.what() << endl;
      return 0; //kills the program
    }
    /*
    for (int e=0; e<n; e++)
    {
      B[e].median=0.4*median(B[e].A)+0.6*B[e].egz;
    }
    for (int e=0; e<n; e++)
    {
      B[e].average=0.4*average(B[e].A)+0.6*B[e].egz;
    }*/
    calculate(B);
    output (n, B);//isvedimo funkcija
 }

  return 0;
}
