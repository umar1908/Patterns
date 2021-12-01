#include<iostream>
#include<string>
#include<list>

class FacebookApi;
class VkApi;

//Абстрактный посетитель
class AbstractVisitor{
public:

  virtual void visit(FacebookApi*) const=0;

  virtual void visit(VkApi*) const =0;

};

//Абстрактный класс, функционал потомков которого будет расширяться
class AbstractApi{
protected:
  std::string name;
public:

  virtual ~AbstractApi()=default;

  virtual void Accept(AbstractVisitor* )=0;

  virtual std::string GetName() const=0;

  AbstractApi(std::string _name):name(_name){}

};


//Первая конкретизация абстрактного класса
class FacebookApi:public AbstractApi{
public:

  virtual ~FacebookApi()=default;

  FacebookApi():AbstractApi("Facebook"){}

  void FacebookSendRequest(std::string request){
    std::cout<<"Request ("<<request<<") has been executed by FacebookApi\n";
  }

  virtual void Accept(AbstractVisitor* visitor) override{
    visitor->visit(this);
  }

  virtual std::string GetName() const override {
    return name;
  }

};

//Вторая конкретищация абстрактного класса
class VkApi:public AbstractApi{
public:

  virtual ~VkApi()=default;

  VkApi():AbstractApi("Vkontakte"){}

  void VkSendRequest(std::string request){
    std::cout<<"Request ("<<request<<") has been executed by VkApi\n";
  }

  virtual void Accept(AbstractVisitor* visitor) override{
    visitor->visit(this);
  }

  virtual std::string GetName() const override {
    return name;
  }

};

// Первая конкретизация посетителя
class ChangePassword:public AbstractVisitor{
public:
  virtual ~ChangePassword()=default;
private:

  virtual void visit(FacebookApi* api) const override {
    api->FacebookSendRequest("Change Facebook Password ******");
  }

  virtual void visit(VkApi* api) const override {
    api->VkSendRequest("Change Instagram Password ******");
  }


};

// Вторая конкретизация посетителя
class SendMessage:public AbstractVisitor{
public:

  virtual void visit(FacebookApi* api) const override {
    api->FacebookSendRequest("Send message by Facebook");
  }

  virtual void visit(VkApi* api) const override {
    api->VkSendRequest("Send message by Vkontakte");
  }


};




int main(){
  //Создание основных объектов
  FacebookApi facebook;
  VkApi vk;

  //Создание посетителей
  ChangePassword PasswordChanger;
  SendMessage MessageSender;

  // Применение посетителей к основным объектам
  facebook.Accept(&PasswordChanger);
  vk.Accept(&PasswordChanger);

  facebook.Accept(&MessageSender);
  vk.Accept(&MessageSender);





  return 0;
}
