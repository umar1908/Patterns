#include<iostream>
#include<windows.h>


//3 абстрактные сущности: Команда, Конфигурационный файл, Драйвер
class AbstractCommand{
protected:
  std::string command;
public:
  virtual std::string GetCommandText() const=0;

  virtual void SetCommand(std::string) =0;

  virtual ~AbstractCommand() =default;
};


class AbstractConfig{
protected:
  std::string config;
public:
  virtual void SetConfig(std::string) =0;

  virtual std::string GetConfigText() const=0;

  virtual ~AbstractConfig()=default;

};

class AbstractDriver{
public:
  virtual void execute(const AbstractCommand&) const=0;

  virtual void ShutDown() const=0;

  virtual void ApplyConfig(const AbstractConfig&) const=0;

  virtual ~AbstractDriver()=default;
};


//Конкретизация сущностей на 2 рода: Аудиокарта и Сетевая карта
class AudioCardDriver:public AbstractDriver{

  virtual void execute(const AbstractCommand& command) const override{
      std::cout<<"AudioCard has executed command:"<<command.GetCommandText()<<std::endl;
    }

  virtual void ShutDown() const override{
    std::cout<<"AudioCard was shut down\n";
  }

  virtual void ApplyConfig(const AbstractConfig& config) const override{
    std::cout<<"The new config was applied to AudioCard:"<<config.GetConfigText()<<std::endl;
  }

  virtual ~AudioCardDriver() = default;

};

class AudioCardCommand:public AbstractCommand{

  virtual std::string GetCommandText() const override {
    return command;
  }

  virtual void SetCommand(std::string text) override {
    command="Audio Card Command: " + text;
  }

  virtual ~AudioCardCommand()=default;

};

class AudioCardConfig:public AbstractConfig{

  virtual void SetConfig(std::string text) override {
    config="Audio Card Config: "+text;
  }

  virtual std::string GetConfigText() const override{
    return config;
  }

  virtual ~AudioCardConfig()=default;

};


class NetworkCardDriver:public AbstractDriver{

  virtual void execute(const AbstractCommand& command) const override{
      std::cout<<"NetworkCard has executed command:"<<command.GetCommandText()<<std::endl;
  }

  virtual void ShutDown() const override{
    std::cout<<"Network was shut down\n";
  }

  virtual void ApplyConfig(const AbstractConfig& config) const override{
    std::cout<<"The new config was applied to NetworkCard:"<<config.GetConfigText()<<std::endl;
  }

  virtual ~NetworkCardDriver()=default;

};

class NetworkCardCommand:public AbstractCommand{

  virtual std::string GetCommandText() const override{
    return command;
  }

  virtual void SetCommand(std::string text) override{
    command="Network Card Command: " + text;
  }

  virtual ~NetworkCardCommand()=default;

};


class NetworkCardConfig:public AbstractConfig{

  virtual void SetConfig(std::string text) override{
    config="Network Card Config: "+text;
  }

  virtual std::string GetConfigText() const override{
    return config;
  }

  virtual ~NetworkCardConfig()=default;

};

//Создание Абстрактной фабрики
class AbstractFactory{
public:
     virtual AbstractDriver* CreateDriver() const=0;

     virtual AbstractCommand* CreateCommand() const=0;

     virtual AbstractConfig* CreateConfig() const=0;

     virtual ~AbstractFactory()=default;

};

//Конкретизация фадрики на случай Сетевой и Аудиокарты
class AudioCardFactory:public AbstractFactory{
public:
  virtual AbstractDriver* CreateDriver() const override{
    return new AudioCardDriver();
  }

  virtual AbstractCommand* CreateCommand() const override {
    return new AudioCardCommand();
  }

  virtual AbstractConfig* CreateConfig() const override{
    return new AudioCardConfig();
  }

  virtual ~AudioCardFactory()=default;
};

class NetworkCardFactory:public AbstractFactory{
public:
  virtual AbstractDriver* CreateDriver() const override {
    return new NetworkCardDriver();
  }

  virtual AbstractCommand* CreateCommand() const override {
    return new NetworkCardCommand();
  }

  virtual AbstractConfig* CreateConfig() const override{
    return new NetworkCardConfig();
  }

  virtual ~NetworkCardFactory()=default;
};


//Имитация внешнего использованя реализованного интерфейса
void user(const AbstractFactory& factory){

  AbstractCommand* command=factory.CreateCommand();
  command->SetCommand("Test command");

  AbstractConfig* config=factory.CreateConfig();
  config->SetConfig("Test config");

  AbstractDriver* driver=factory.CreateDriver();
  driver->execute(*command);
  driver->ApplyConfig(*config);
  driver->ShutDown();

  delete command;
  delete config;
  delete driver;
}

int main(){
  // Создание двух по-разному конкретизированных фабрик
  AbstractFactory* factory1 = new AudioCardFactory();
  AbstractFactory* factory2 = new NetworkCardFactory();

  //Передача фабрик для стороннего использованя
  std::cout<<"AudioCard Test:\n\n";
  user(*factory1);
  std::cout<<"\n\nNetworkCard Test:\n\n";
  user(*factory2);

  delete factory1;
  delete factory2;

  return 0;
}
