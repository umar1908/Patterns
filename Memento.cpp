#include<iostream>
#include<stack>
#include<string>



class TextEditor;

//Абстрактный класс хранилища
class AbstractMemento{
private:
  std::string name;
  std::string state;
  int hex;
  TextEditor* original;

public:

  AbstractMemento(std::string _state, int _hex, std::string _name,TextEditor* _original):name(_name),state(_state),hex(_hex),original(_original){}

  virtual std::string GetName() const{
    return name;
  };

  virtual std::string GetState() const{
    return state;
  };

  virtual int GetHex() const{
    return hex;
  };

  virtual TextEditor* GetOriginal()const{
    return original;
  }

  virtual void recover() const=0;

  virtual ~AbstractMemento()=default;

};

//Класс под контролем паттерна снимок
class TextEditor{
private:
  std::string RealState;
  int RealHex;
  // Конкретизация встроенного абстрактного класса хранилища
  class TextMemento:public AbstractMemento{

      friend TextEditor; // Как ни парадоксально - обеспечивает инкапсуляцию, а не наоборот

    private:

        TextMemento(const std::string& str, const int& _hex,std::string name, TextEditor* original):AbstractMemento(str,_hex,name,original){}

    public:

      TextMemento()=delete;
      virtual void recover() const override{
        GetOriginal()->RealState=GetState();
        GetOriginal()->RealHex=GetHex();
      }

      virtual ~TextMemento()=default;

      };

public:

  void EditText(const std::string& text){
    RealState=text;
  }

  void EditHex(const int& hex ){
    RealHex=hex;
  }

  void Status(){
    std::cout<<"Current status:\nText:"<<RealState<<"\nHex:"<<RealHex<<"\n\n";
  }

  TextMemento* CreateMemento(std::string name="Unnamed") {
    return new TextMemento(RealState, RealHex, name,this);
  }

};

//Класс Опекуна
class Caretaker{
private:
  std::stack<AbstractMemento*> history;
  TextEditor* original;
public:

  Caretaker(TextEditor* _original):original(_original){}

  void Save(std::string name="Unnamed") {
    history.push(original->CreateMemento(name));
  }

  void Undo(){
    if(history.size()==0) throw std::range_error("History is empty");
    history.top()->recover();
    history.pop();
  }

  ~Caretaker(){
    for (size_t i = 0; i < history.size(); i++) {
      delete history.top();
      history.pop();
    }
  }

};


int main(){
  TextEditor t1;
  Caretaker backup(&t1);

  //Последовательное изменение данных и сохранение изменений опекуном
  t1.EditText("text1");
  t1.EditHex(1);
  t1.Status();
  backup.Save();

  t1.EditText("text2");
  t1.EditHex(2);
  t1.Status();
  backup.Save();

  t1.EditText("text3");
  t1.EditHex(3);
  t1.Status();
  backup.Save();

  //Последовательная отмена изменений
  backup.Undo();
  t1.Status();
  backup.Undo();
  t1.Status();
  backup.Undo();
  t1.Status();

  // backup.Undo();
  // t1.Status();




}
