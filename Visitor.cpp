#include<iostream>
#include<string>
#include<list>

class FacebookApi;
// class InstagramApi;
class VkApi;
// class TwitterApi;

class AbstractVisitor{
public:
  virtual void visit(FacebookApi*) const=0;
  virtual void visit(VkApi*) const =0;


};


class AbstractApi{
protected:
  std::string name;
public:
  virtual ~AbstractApi()=default;
  virtual void Accept(AbstractVisitor* )=0;
  virtual std::string GetName() const=0;
  AbstractApi(std::string _name):name(_name){}

};



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

class ChangePassword:public AbstractVisitor{
  virtual void visit(FacebookApi* api) const override {
    api->FacebookSendRequest("Change Facebook Password ******");
  }

  virtual void visit(VkApi* api) const override {
    api->VkSendRequest("Change Instagram Password ******");
  }


};



class SendMessage:public AbstractVisitor{
  virtual void visit(FacebookApi* api) const override {
    api->FacebookSendRequest("Send message by Facebook");
  }

  virtual void visit(VkApi* api) const override {
    api->VkSendRequest("Send message by Vkontakte");
  }


};




int main(){
  FacebookApi facebook;
  VkApi vk;

  ChangePassword PasswordChanger;
  SendMessage MessageSender;

  facebook.Accept(&PasswordChanger);
  vk.Accept(&PasswordChanger);

  facebook.Accept(&MessageSender);
  vk.Accept(&MessageSender);





  return 0;
}
