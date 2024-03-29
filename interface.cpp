#include "interface.hpp"
#include "iomanip"

extern void tests();
extern void testsb();
extern void testsc();
extern void testse();
extern void testsl();

//menu glowne
void main_menu(Owner &ow)
{
  char choice[2], choice2[2];
  choice[0] = '0';

  while(choice[0] != '5'){
    std::cout<<std::endl<<"Wybierz osobe"<<std::endl;
    std::cout<<"1. Wlasciciel"<<std::endl;
    std::cout<<"2. Pracownik"<<std::endl;
    std::cout<<"3. Klient"<<std::endl;
    std::cout<<"4. Testy"<<std::endl;
    std::cout<<"5. Koniec"<<std::endl;
    load(choice, 2);
    switch (choice[0])
    {
      case '1': //wlasciciel
        bs_menu1(ow);
        break;
      case '2': //pracownik
        if(ow.get_firstBs() == NULL)
          std::cout<<"Nie powstala jeszcze zadna ksiegarnia. Nie moze byc zadnego pracownika."<<std::endl;
        else
          em_menu1(ow);
        break;
      case '3': //klient
        if(ow.get_firstBs() == NULL)
          std::cout<<"Nie powstala jeszcze zadna ksiegarnia. Nie moze byc zadnego klienta."<<std::endl;
        else
          cu_menu1(ow);
        break;
      case '4': //testy
        std::cout<<"TESTY"<<std::endl<<"1. Test klasy Bookshop"<<std::endl<<"2. Test klasy Book"<<std::endl;
        std::cout<<"3. Test klasy Customer"<<std::endl<<"4. Test klasy Employee"<<std::endl<<"5. Test szablonu klasy List"<<std::endl;
        load(choice2, 2);
        if(choice2[0] == '1')
          tests();
        else if(choice2[0] == '2')
          testsb();
        else if(choice2[0] == '3')
          testsc();
        else if(choice2[0] == '4')
          testse();
        else if(choice2[0] == '5')
          testsl();
      break;
      case '5':
        break;
      default:
        std::cout<<"Nie ma takiej mozliwosci"<<std::endl;
        break;
    }
  }
}

//menu wlasciciela ksiegarni - ogolne
void bs_menu1(Owner &ow)
{
  int number;
  char choice[2];
  choice[0] = '0';

  while(choice[0] != '5'){
    std::cout<<std::endl<<"Wlasciciel: "<<ow.get_name()<<" "<<ow.get_surname()<<" "<<fixed<<setprecision(2)<<ow.get_budget()<<std::endl;
    std::cout<<"1. wyswietl liste ksiegarni"<<std::endl;
    std::cout<<"2. stworz nowe ksiegarnie"<<std::endl;
    std::cout<<"3. usun ksiegarnie"<<std::endl;
    std::cout<<"4. zarzadzaj ksiegarnia"<<std::endl;
    std::cout<<"5. wyjscie"<<std::endl;
    load(choice, 2);
    switch(choice[0])
    {
      case '1':
        if(ow.get_firstBs() == NULL) std::cout<<"Nie ma jeszcze zadnych ksiegarni"<<std::endl;
        else ow.show_bs();
        break;
      case '2':
        ow.new_bs();
        break;
      case '3':
        if(ow.get_firstBs() == NULL)
          std::cout<<std::endl<<"Nie ma jeszcze zadnych ksiegarni. Nie mozna zadnej usunac."<<std::endl;
        else
        {
          ow.show_bs();
          std::cout<<std::endl<<"Wybierz numer ksiegarni, ktora chcesz usunac"<<std::endl;
          number = load_n();
          ow.delete_bs(number);
        }
        break;
      case '4':
        if(ow.get_firstBs() == NULL)
          std::cout<<std::endl<<"Nie istnieje jeszcze zadna ksiegarnia. Nie mozna zarzadzac ksiegarniami."<<std::endl;
        else
          bs_menu2(ow);
        break;
      case '5':
        break;
      default:
        std::cout<<"Nie ma takiej mozliwosci"<<std::endl;
        break;
    }
  }
}

//menu wlasciciela ksiegarni - ksiegarnia
void bs_menu2(Owner &ow)
{
  List<Bookshop> *currBs = ow.get_firstBs();;
  Bookshop *bs;
  List<Employee> *em;
  double sum = 0;
  char choice[2];
  int number;
  choice[0] = '0';

  while(choice[0] != '8'){
    bs = currBs->get_obj();
    std::cout<<std::endl<<"Ksiegarnia "<<bs->get_name()<<" w miescie "<<bs->get_city()<<std::endl;
    std::cout<<"1. Wyswietl liste pracownikow"<<std::endl;
    std::cout<<"2. Zatrudnij nowego pracownika"<<std::endl;
    std::cout<<"3. Zwolnij pracownika"<<std::endl;
    std::cout<<"4. Wyplac pensje pracownikom"<<std::endl;
    std::cout<<"5. Zarzadzaj zamowieniami"<<std::endl; //akceptowanie/odrzucanie
    std::cout<<"6. Odbierzu utarg"<<std::endl;
    std::cout<<"7. Nastepna ksiegarnia"<<std::endl;
    std::cout<<"8. Wyjscie"<<std::endl;
    load(choice, 2);

    switch(choice[0])
    {
      case '1':
        bs->show_employees();
        break;
      case '2':
        bs->new_employee();
        break;
      case '3':
        if(bs->get_firstE() == NULL)
          std::cout<<std::endl<<"W tej ksiegarni nie ma jeszcze zadnych pracownikow. Nie mozna nikogo zwolnic"<<std::endl;
        else
        {
          bs->show_employees();
          std::cout<<std::endl<<"Wybierz numer pracownika, ktorego chcesz usunac."<<std::endl;
          number = load_n();
          bs->delete_employee(number);
        }
        break;
      case '4':
        if((em = bs->get_firstE()) == NULL)
          std::cout<<"W tej ksiegarni nikt jeszcze nie pracuje. Zatrudnij pracownika, aby wyplacic mu pensje."<<std::endl;
        else
        {
          do
          {
            sum += em->get_obj()->get_salary();
            em = em->get_next();
          }while(em != bs->get_firstE());
          if(bs->get_budget()<sum) {std::cout << "Za maly budzet " << std::endl; break;}
          else (*bs) - sum;
        }
        break;
      case '5':
        ow.accept(bs);
        break;
      case '6':
        ow.get_cash(bs);
        break;
      case '7':
        currBs = currBs->get_next();
        break;
      case '8':
        break;
      default:
        std::cout<<"Nie ma takiej mozliwosci"<<std::endl;
        break;
    }
  }
}

//menu pracownika - ogolne
void em_menu1(Owner &ow)
{
  char choice[2];
  int number;
  List<Bookshop> *currBs = ow.get_firstBs();
  Bookshop *bs;
  List<Employee> *currEm;
  choice[0] = '0';

  while(choice[0] != '3')
  {
    bs = currBs->get_obj();
    currEm = bs->get_firstE();
    std::cout<<std::endl<<"PRACOWNIK - ksiegarnia "<<bs->get_name()<<" w miescie "<<bs->get_city()<<std::endl;
    std::cout<<"1. Wybierz pracownika"<<std::endl;
    std::cout<<"2. Przejdz do nastepnej ksiegarni"<<std::endl;
    std::cout<<"3. Wyjscie"<<std::endl;
    load(choice, 2);

    switch(choice[0])
    {
      case '1':
        if(bs->get_firstE() == NULL)
          std::cout<<std::endl<<"W danej ksiegarni nie ma jeszcze zadnego pracownika. Nie mozna sie w zadnego wcielic."<<std::endl;
        else
        {
          bs->show_employees();
          std::cout<<"Wybierz numer pracownika, w ktorego chcesz sie wcielic"<<std::endl;
          number = load_n();
          for(int i = 1 ; i < number ; i++)
            currEm = currEm->get_next();
          em_menu2(currEm->get_obj(), bs);
        }
      case '2':
        currBs = currBs->get_next();
        break;
      case '3':
        break;
      default:
        std::cout<<"Nie ma takiej mozliwosci."<<std::endl;
        break;
    }
  }
}

//menu pracownika - konkretny pracownik
void em_menu2(Employee *em, Bookshop *bs)
{
  int number;
  char choice[2];
  choice[0] = '0';
  if(em != NULL  && bs != NULL)
  {
    while(choice[0] != '6'){
      std::cout<<std::endl<<"Pracownik "<<em->get_name()<<" "<<em->get_surname()<<std::endl;
      std::cout<<"\"Hmm... co by tu zrobic?\""<<std::endl;
      std::cout<<"1. Pokaz liste wszystkich ksiazek"<<std::endl;
      std::cout<<"2. Dopisz ksiazke do zamowienia"<<std::endl;
      std::cout<<"3. Zloz zamowienie"<<std::endl;
      std::cout<<"4. Wyswietl aktualne zamowienie"<<std::endl;
      std::cout<<"5. Wycofaj ksiazke z ksiegarni"<<std::endl;
      std::cout<<"6. Stan za kasa i czekaj na klientow"<<std::endl;
      load(choice, 2);
      switch(choice[0])
      {
        case '1':
          bs->show_books();
          break;
        case '2':
          bs->new_book();
          std::cout<<"Zamowienie zostalo zlozone"<<std::endl;
          break;
        case '3':
          if(bs->get_firstB() != NULL)
            bs->order_e();
          else
            std::cout<<"Do ksiegarni nie zostala przypisana jeszcze zadna ksiazka. Nie mozna zadnej zamowic."<<std::endl;
          break;
        case '4':
          bs->show_order();
          break;
        case '5':
          bs->show_books();
          number = load_n();
          bs->delete_book(number);
        case '6':
          break;
        default:
          std::cout<<"Nie ma takiej mozliwosci."<<std::endl<<std::endl;
      }
    }
  }
  else std::cout<<"Blad: w tej ksiegarni nie ma jeszcze zadnych pracownikow"<<std::endl;
}

//menu klienta - ogolne
void cu_menu1(Owner &ow)
{
  char choice[2];
  int number;
  List<Bookshop> *currBs = ow.get_firstBs();
  List<Customer> *currCu;
  Bookshop *bs = currBs->get_obj();
  choice[0] = '0';
  if(currBs != NULL)
  {
    while(choice[0] != '6')
    {
      currCu = currBs->get_obj()->get_firstC();
      std::cout<<std::endl<<"KLIENT - ksiegarnia "<<bs->get_name()<<" w miescie "<<bs->get_city()<<std::endl;
      std::cout<<"1. Wyswietl liste klientow"<<std::endl;
      std::cout<<"2. Stworz nowego klienta"<<std::endl;
      std::cout<<"3. Usun klienta"<<std::endl;
      std::cout<<"4. Wybierz klienta"<<std::endl;
      std::cout<<"5. Przejdz do nastepnej ksiegarni"<<std::endl;
      std::cout<<"6. Wyjscie"<<std::endl;
      load(choice, 2);

      switch (choice[0])
      {
        case '1':
          bs->show_customers();
          break;
        case '2':
          bs->new_customer();
          break;
        case '3':
          if(bs->get_firstC() == NULL)
            std::cout<<std::endl<<"W tej ksiegarni nie ma jeszcze zadnych klientow."<<std::endl;
          else
          {
            bs->show_customers();
            std::cout<<std::endl<<"Wybierz numer klienta, ktorego chcesz usunac."<<std::endl;
            number = load_n();
            bs->delete_customer(number);
          }
          break;
        case '4':
          if(bs->get_firstC() == NULL)
            std::cout<<std::endl<<"W danej ksiegarni nie ma jeszcze zadnych klientow. Nie mozna zadnego wybrac."<<std::endl;
          else if(bs->get_firstE() == NULL)
            std::cout<<"Ksiegarnia zamknieta do odwolania. (Brak pracownikow)"<<std::endl;
          else
          {
            bs->show_customers();
            std::cout<<"Wybierz numer klienta, w ktorego chcesz sie wcielic"<<std::endl;
            number = load_n();
            for(int i = 1 ; i < number ; i++)
              currCu = currCu->get_next();
            cu_menu2(currCu->get_obj(), bs);
          }
          break;
        case '5':
          currBs = currBs->get_next();
          break;
        case '6':
            break;
        default:
          std::cout<<"Nie ma takiego wyboru."<<std::endl;
          break;
      }
    }
  }
  else
    std::cout<<"Nie istnieje jeszcze zadna ksiegarnia. Nie moze byc zadnych klientow"<<std::endl;
}

//menu klienta - konkretny klient
void cu_menu2(Customer *cu, Bookshop *bs)
{
  List<Book> *currBo;
  char choice[2];
  int number, i;
  choice[0] = '0';

  while(choice[0] != '7'){
    std::cout<<"Klient "<<cu->get_name()<<" "<<cu->get_surname()<<std::endl;
    std::cout<<"Ksiegarnia"<<bs->get_name()<<" w miescie "<<bs->get_city()<<std::endl;
    std::cout<<"1. Obejrzyj ksiazki"<<std::endl;
    std::cout<<"2. Kup ksiazke"<<std::endl;
    std::cout<<"3. Zamow ksiazke"<<std::endl;
    std::cout<<"4. Idz do pracy (zarabiac na nowe ksiazki)"<<std::endl;
    std::cout<<"5. Przejrzyj swoja kolekcje"<<std::endl;
    std::cout<<"6. Sprawdz zawartosc portfela"<<std::endl;
    std::cout<<"7. Wyjdz z ksiegarni"<<std::endl;
    load(choice, 2);

    switch(choice[0])
    {

      case '1':
        bs->show_books_c();
        break;
      case '2':
        i = 0;
        currBo = bs->get_firstB();
        number = bs->show_books_c();
        if(currBo != NULL && number >0)
        {
          std::cout<<"-Poprosze ksiazke z numerem...";
          number = load_n();

          while(true)  //ustawianie wskaznika na wybrana przez klienta ksiazke
          {
            if(currBo->get_obj()->get_number() > 0)  i++;
            if(i == number)  break;
              currBo = currBo->get_next();
          }
          cu->buy(*(currBo->get_obj()));
        }

        else  std::cout<<"Nie moge nic kupic."<<std::endl;
        break;
      case '3':
        bs->new_book();
        std::cout<<"Zamowienie zostalo zlozone"<<std::endl;
        break;
      case '4':
        *cu += 100.0;
        break;
      case '5':
        cu->show_collection();
        break;
      case '6':
        std::cout<<"W portfelu znajduje sie "<<cu->get_money()<<"zl"<<std::endl;
        break;
      case '7':
        std::cout<<"-Do widzenia."<<std::endl<<"-Do widzenia."<<std::endl;
        break;
      default:
        std::cout<<"Nie ma takiej mozliwosci"<<std::endl;
        break;
    }
  }
}
