#include<iostream>
#include<list>
#include<string>
#include<algorithm>

class Node{
protected:
  std::string ip;
  Node* parent;
public:
  Node(std::string _ip):ip(_ip),parent(nullptr){};
  virtual ~Node()=default;
  virtual void SetParent(Node*) = 0;
  virtual Node* GetParent() const = 0;
  virtual void Add(Node*) = 0;
  virtual void Remove(Node*) = 0;
  virtual std::string operator()() const=0;
  virtual bool isComputer()const=0;
  virtual void info() const=0;
};


class Computer:public Node{
public:
  Computer(std::string _ip):Node(_ip){};

  virtual ~Computer()=default;

  virtual void SetParent(Node* _parent) override {
    parent=_parent;
  }

  virtual Node* GetParent() const override {
    return parent;
  }

  virtual void Add(Node* child) override {
    throw "Attempt to add node to Computer\n";
  }

  virtual void Remove(Node*) override {
    throw "Attempt to remove node from Computer\n";
  }

  virtual std::string operator()() const override {
    return ip;
  }

  virtual bool isComputer()const override{
    return true;
  }

  virtual void info() const override {
    std::cout<<"This is computer with ip:"<<ip<<std::endl;
  }

};

class Router:public Node{
private:
  std::list<Node*> childs;
public:
  Router(std::string _ip):Node(_ip){};
  virtual ~Router()=default;

  virtual void SetParent(Node* _parent) override {
    parent=_parent;
  }
  virtual Node* GetParent() const override {
    return parent;
  }

  virtual void Add(Node* child) override {
    if( std::find(childs.begin(),childs.end(),child)==childs.end() ){
      childs.push_back(child);
      child->SetParent(this);
    }
  }

  virtual void Remove(Node* child) override {
    childs.remove(child);
  }
  virtual std::string operator()() const override {
    std::string buffer{};
    for(const auto&  elem: childs){
      buffer+=elem->operator()()+"\n";
    }
    return ip+"\n"+buffer;
  }
  virtual bool isComputer()const override {
    return false;
  }

  virtual void info() const override {
    std::cout<<"This is router with ip:"<<ip<<std::endl;
  }

};

void Client(const Node& node){
  std::cout<<"Current node info:\n";
  node.info();
  std::cout<<"Device list:\n"<<node();
  std::cout<<"\n\n\n";


}


int main(){
  Router r1("192.168.1.1");
  Router r2("192.168.1.2");
  Router r3("192.168.1.3");
  Computer c1("192.168.2.1");
  Computer c2("192.168.2.2");
  Computer c3("192.168.2.3");
  Computer c4("192.168.2.4");
  Computer c5("192.168.2.5");
  Computer c6("192.168.2.6");

  r1.Add(&c1);
  r1.Add(&c2);
  r1.Add(&r2);
  r2.Add(&c3);
  r2.Add(&c4);
  r2.Add(&c5);
  r2.Add(&r3);
  r3.Add(&c6);

  Client(r1);
  Client(r2);
  Client(c5);
  

  return 0;
}
