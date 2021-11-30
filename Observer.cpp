#include<iostream>
#include<list>
#include<algorithm>

class AbstractPublisher;

//Абстрактный класс наблюдателя
class AbstractObserver{
protected:
  std::string name;
public:

  AbstractObserver(std::string _name):name(_name){};

  virtual void update(const AbstractPublisher*)=0;

  std::string GetName() const{
    return name;
  }

};

//Абстрактный класс издателя
class AbstractPublisher{
protected:
  std::string name;
  std::list<AbstractObserver*> subs;
  std::string text;
public:

   virtual void SetName(const std::string&)=0;

   virtual std::string GetName() const=0;

   virtual void Attach(AbstractObserver* observer)=0;

   virtual void Detach(AbstractObserver* observer)=0;

   virtual void Notify()const=0;

   virtual std::string GetText() const=0;

   virtual void SetText(const std::string&) =0;

   virtual ~AbstractPublisher()=default;
};

//Конкретизированный класс издателя
class Publisher:public AbstractPublisher{
public:

  virtual ~Publisher()=default;

  virtual void Attach(AbstractObserver* observer) override{
   if (std::find(subs.begin(),subs.end(), observer)==subs.end()){
     subs.push_back(observer);
     std::cout<<observer->GetName()<<" has sunscribed to "<<GetName()<<"\n\n";
   }
 }

 virtual void Detach(AbstractObserver* observer) override {
  subs.remove(observer);
  std::cout<<observer->GetName()<<" has unsunscribed from "<<GetName()<<"\n\n";
}

  virtual void Notify() const override {
    std::cout<<GetName()<<" notified his subscribers!\n\n";
    for(const auto& elem:subs){
      elem->update(this);
    }
  }

  virtual std::string GetText() const override {
    return text;
  };

  virtual void SetText(const std::string& _text) override {
    text=_text;
  };

  virtual void SetName(const std::string& _name) override{
    name=_name;
  }

  virtual std::string GetName() const override{
    return name;
  }

};

//Конкретизированный класс наблюдателя
class Observer:public AbstractObserver{
private:

public:

  virtual ~Observer()=default;

  Observer(std::string _name="Nnnamed"):AbstractObserver(_name){};


  virtual void update(const AbstractPublisher* publisher) override{
    std::cout<<name<<": The new message has been received from: "<<publisher->GetName()<<"\nText:\n"<<publisher->GetText()<<"\n\n";
  }

};



int main(){
  //Создание экземпляров издателя
  Publisher p1,p2;
  p1.SetName("Publisher1");
  p2.SetName("Publisher2");

  //Создание экземпляров наблюдателей
  Observer sub1("Subscriber 1"),sub2("Subscriber 2");

  //Подписка на первое издание
  p1.Attach(&sub1);
  p1.Attach(&sub2);

  //Изменение текста сообщения
  p1.SetText("Test message 1");
  p2.SetText("Test message 2");

  //Уведомление подписчиков
  p1.Notify();
  p2.Notify();

  //Отписка первого наблюдателя от первого издания
  p1.Detach(&sub1);

  //Уведомление подписчиков первого издания
  p1.Notify();

  //Подписка второго наблюдателя на второго издателя
  p2.Attach(&sub2);
  //Уведомление подписчиков первого и второго издателя
  p2.Notify();
  p1.Notify();


  return 0;
}
