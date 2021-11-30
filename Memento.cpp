#include<iostream>
#include<stack>
#include<string>

//ПРОВЕРИТЬ CONST и OVERRIDE И ВИРТУАЛЬНЫЙ КОСТУРУКТОР
//РЕАЛИЗОВАТЬ ХРАНИЛИЩЕ ДАМПОВ СО СТЕКОМ

class AbstractMemento{
protected:
  std::string name;
  std::string state;
  int hex;
public:
  virtual std::string GetName() const=0;
  virtual std::string GetSate() const=0;
  virtual int GetHex() const=0;
  virtual ~AbstractMemento()=default;

};


class TextEditor{
private:
  std::string RealState;
  int RealHex;

  class TextMemento:public AbstractMemento{
  public:
    TextMemento(const std::string& str, const int& _hex,std::string name){
      state=str;
      hex=_hex;
    }
    virtual std::string GetName() const override{
      return name;
    }
    virtual std::string GetSate() const override{
      return state;
    }
    virtual int GetHex() const override{
      return hex;
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
    std::cout<<"Current status:\nText:"<<RealState<<"\nHex:"<<RealHex<<std::endl;
  }

  TextMemento CreateMemento(std::string name="Unnamed") const{
    return TextMemento(RealState, RealHex, name);
  }

  void Recover(TextMemento mem){
    RealState=mem.GetSate();
    RealHex=mem.GetHex();
  }


};


int main(){
  TextEditor t1;
  t1.EditText("text version 1");
  t1.EditHex(123);
  t1.Status();

  auto mem=t1.CreateMemento("version 1");

  t1.EditText("text version 2");
  t1.EditHex(0);
  t1.Status();

  t1.Recover(mem);
  t1.Status();

}
