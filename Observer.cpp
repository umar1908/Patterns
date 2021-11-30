#include<iostream>
#include<list>
#include<algorithm>

class AbstractPublisher;

// СДЕЛАТЬ ДЕСТРУКТОРЫ ВИРТУАЛЬНЫМИ!
// ПРОВЕРИТЬ OVERRIDE и CONST
class AbstractObserver{
public:
  virtual void update(const AbstractPublisher*)=0;
  // virtual AbstractObserver
};

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
};

class Publisher:public AbstractPublisher{
public:
  virtual void Attach(AbstractObserver* observer) override{
   if (std::find(subs.begin(),subs.end(), observer)==subs.end()){
     subs.push_back(observer);
     std::cout<<"\nAttached!\n";
   }
 }

 virtual void Detach(AbstractObserver* observer) override {
  subs.remove(observer);
}

  virtual void Notify() const override {
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

  virtual std::string GetName() const{
    return name;
  }

};


class Observer:public AbstractObserver{
private:
  std::string name;
public:
  virtual void update(const AbstractPublisher* publisher){
    std::cout<<"The new message has been received from :"<<publisher->GetName()<<"\nText:\n"<<publisher->GetText()<<std::endl;
  }


};


int main(){
  Publisher p1,p2;
  p1.SetName("Publisher1");
  p2.SetName("Publisher2");

  Observer sub1,sub2;

  p1.Attach(&sub1);
  p2.Attach(&sub2);


  p1.SetText("Text1");
  p2.SetText("Text2");

  p1.Notify();
  p2.Notify();

  p1.Detach(&sub1);
  p2.Detach(&sub2);

  p1.Notify();
  p2.Notify();


  return 0;
}
