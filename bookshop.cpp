#include "bookshop.hpp"
extern

int Bookshop::numBookshops = 0;

//konstruktor
Bookshop::Bookshop(std::string n, std::string c, double b): name(n), city(c), budget(b), firstB(NULL), order(NULL), firstE(NULL), firstC(NULL), oA(0)
{
  numBookshops++;
  D(std::cout <<"Tworze ksigarnie"<<std::endl;)
}

//destruktor
Bookshop::~Bookshop()
{
  while(firstB != NULL)    firstB = delete_o(1, firstB);
  while(firstE != NULL)    firstE = delete_o(1, firstE);
  while(firstC != NULL)    firstC = delete_o(1, firstC);
  while(order != NULL)    order = delete_o(1, order);
  D(std::cout <<"Niszcze ksigarnie"<<std::endl;)
  numBookshops--;
}

//przeciazenie operatora przypisania
Bookshop& Bookshop::operator= (Bookshop &b2)
{
  this->name = b2.get_name();
  this->city = b2.get_city();
  this->budget = b2.get_budget();
  this->oA = 0;
  return *this;
}

//przeciazenie operatora wyjscia
std::ostream& operator<< (std::ostream &os, Bookshop *b)
{
  os<<b->get_name()<<" "<<b->get_city()<<" "<<b->get_budget()<<std::endl;
  return os;
}

//UWAGA: DOPRACOWAC WYSWIETLANIE - KLIENTOM NI MOZE WYSWIETLAC SIE LISTA, JESLI NIE MA ZADNYCH EGZEMPLARZY!
//wyswietla liste ksiazek, zwraca liczbe ksiazek "dostepnych" w zaleznosci od tego kto widzi liste
void Bookshop::show_books(){if(firstB == NULL) std::cout<<"Nie ma jeszcze zadnych ksiazek"<<std::endl; show_l(firstB);}

//wyswietla liste klientow ksiegarni
void Bookshop::show_customers(){if(firstC == NULL) std::cout<<"Nie ma jeszcze zadnych klientow"<<std::endl; else {std::cout<<"Lista ksiazek:"<<std::endl; show_l(firstC);}}

//wyswietla liste pracownikow, zwraca ich liczbe
void Bookshop::show_employees(){if(firstE == NULL) std::cout<<"Nie ma jeszcze zaznych pracownikow"<<std::endl; else {std::cout<<"Lista pracownikow:"<<std::endl; show_l(firstE);}}

//wyswietla aktywne zamowienie
void Bookshop::show_order(){if(oA == 0 || order == NULL) std::cout<<"Zadne zamowienie nie jest aktualnie zlozone"<<std::endl;  else  {std::cout<<"Zamowienie:"<<std::endl; show_l(order);}}

//zbiera informacje o ksiazce, ktora ma zostac stworzona, dodaje ja do listy
void Bookshop::new_book()
{
  List<Book> *bo;
  string t, a, p;
  int no, y, pag;
  double pr;

  srand(time(NULL));
  y = rand()%50+1967;
  pag = rand()%400+154;
  std::cout<<"Tytul: ";                                                        std::cin>>t;
  std::cout<<"Autor: ";                                                        std::cin>>a;
  std::cout<<"Wydawca: ";                                                      std::cin>>p;
  std::cout<<"Ilosc zamawianych egzemplarzy: ";                                std::cin>>no;
  std::cout<<"Cena egzemplarza w hurtowni: "<<quantity_pr(y, pag)<<std::endl;
  std::cout<<"Ustal cene ksiazki w ksiegarni: ";                               std::cin>>pr;

  Book b(t, a, p, pr, y, pag, 0, no);
  if((bo = find_o(b, firstB)) != NULL){bo->get_obj()->set_nOrd(bo->get_obj()->get_nOrd() + no - bo->get_obj()->get_number());}
  else{firstB = new_o(firstB, b);}
}

//tworzy nowego klienta na podstawie wprowadzonych danych, umieszcza go na koncu listy klientow, zwraca nan wskaznik
void Bookshop::new_customer()
{
  std::string n, s;
  double m;

  std::cout<<"Imie: ";         std::cin>>n;
  std::cout<<"Nazwisko: ";     std::cin>>s;
  std::cout<<"Pieniadze: ";    std::cin>>m;

  Customer c(n, s, m);
  firstC = new_o(firstC, c);
}

//tworzy nowego pracownika na podstawie wybranych przez uzytkonika danych
void Bookshop::new_employee()
{
  std::string n, s;
  double sal;

  std::cout<<"Nowy pracownik: "<<std::endl;
  std::cout<<"Imie: ";       std::cin>>n;
  std::cout<<"Nazwisko: ";   std::cin>>s;
  std::cout<<"Pensja: ";     std::cin>>sal;

  Employee e(n, s, sal);
  firstE = new_o(firstE, e);
}

//wysylanie zamowienia (w domysle: przez pracownika)
void Bookshop::order_e()
{
  int n = -1;
  List<Book> *curr = firstB;

  if(firstB != NULL)
  {
    std::cout<<"Tworzenie zamowienia:"<<std::endl;
    do
    {
      std::cout<<"\""<<curr->get_obj()->get_name()<<"\"  "<<curr->get_obj()->get_author()<<"  "<<curr->get_obj()->get_publisher()<<std::endl;
      std::cout<<"Ilosc potrzebnych egzemplarzy: "<<curr->get_obj()->get_nOrd()<<std::endl;

      while(n < curr->get_obj()->get_nOrd()){std::cout<<"Zamow: ";  std::cin>>n;}
      if(n > 0)
      {
        curr->get_obj()->set_nOrd(n);               //ustawianie odpowiedniego nOrd (dla operatora przypisania w new_o)
        order = new_o(order, *(curr->get_obj()));
        curr->get_obj()->set_nOrd(0);               //zerowanie liczby zamowionych egzemplarzy
      }
      curr = curr->get_next();
    }while(curr != firstB);

    if(this->get_order() != NULL)
    {
      std::cout<<"Zlozono zamowienie: "<<std::endl;
      show_l(order);
      this->set_oA(1);
    }
  }
}

//usuwa ksiazke o zadanym numerze, zwraca do budzetu 30% ceny hurtowej egzemplarzy
void Bookshop::delate_book(int n)
{
  int i;
  List<Book> *current = firstB;

  for(i = 1 ; i < n ; i++)
    current = current->get_next();
  budget -= 0.3*quantity_pr(current->obj.get_year(), current->obj.get_pages());
  firstB = delete_o(n, firstB);
}

//usuwa klienta, ktorego numer zostal dany
void Bookshop::delete_customer(int n)
{
  int i;
  List<Customer> *current = firstC;

  for(i = 1 ; i < n ; i++)
    current = current->get_next();
  firstC = delete_o(n, firstC);
}

//usuwa pracownika, ktorego numer zostal dany
void Bookshop::delete_employee(int n)
{
  int i;
  List<Employee> *current = firstE;

  for(i = 1 ; i < n ; i++)
    current = current->get_next();
  budget -= current->get_obj()->get_salary();
  firstE = delete_o(n, firstE);
}

//wyszukuje z listy ksiazke o zadanym tytule, autorze, wydawnictwie, kategorii i zwraca na nia wskaznik
List<Book>* Bookshop::find_book(std::string t, std::string a, std::string p)
{
  Book b(t, a, p);
  return find_o(b, firstB);
}
