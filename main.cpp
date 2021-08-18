#include <concepts>
#include <string>
#include <iostream>

using namespace std;

template<typename T>
concept LoggerServiceInterface = requires(T logger, const string& str) {
    logger.info(str);
    logger.warn(str);
    logger.error(str);
};
template<typename T>
concept LoggerServiceProvider = requires(T provider){
    {provider.logger} -> LoggerServiceInterface;
};
struct LoggerServiceImpl {
    void info(const string& msg){cout << "[INFO]" << msg << endl;}
    void warn(const string& msg){cout << "[WARN]" << msg << endl;}
    void error(const string& msg){cout << "[ERROR]" << msg << endl;}
};


template<typename T>
concept DataPersistenceInterface = requires(T persistence) {
    persistence.write();
    persistence.read();
    persistence.remove();
};
template<typename T>
concept DataPersistenceProvider = requires(T provider){
    {provider.persistence} -> DataPersistenceInterface;
};
struct DataPersistenceImpl {
    void write(){}
    void read(){}
    void remove(){}
};


template<typename T>
concept CalculatorInterface = requires(T calculator) {
    calculator.add();
    calculator.subtract();
    calculator.reset();
};
template<typename T>
concept CalculatorProvider = requires(T provider){
    {provider.calculator} -> CalculatorInterface;
};
struct CalculatorImpl {
    void add(){}
    void subtract(){}
    void reset(){}
};



template<typename T>
concept ServiceProviderInterface =
        LoggerServiceProvider<T> &&
        DataPersistenceProvider<T> &&
        CalculatorProvider<T>;



void all(ServiceProviderInterface auto provider) {
    provider.logger.info("Hello Logger DI: all");
}


template<typename T>
concept TwoProvider = LoggerServiceProvider<T> && DataPersistenceProvider<T>;
void two(TwoProvider auto provider) {
    provider.logger.info("Hello Logger DI: two");
}

void onlyLogger(LoggerServiceProvider auto provider) {
    provider.logger.info("Hello Logger DI: onlyLogger");
}

void onlyPersist(DataPersistenceProvider auto provider) {
    provider.persistence.write();
}

void onlyCalculator(CalculatorProvider auto provider) {
    provider.persistence.write();
}


struct ServiceProviderImpl{
    LoggerServiceImpl logger;
    DataPersistenceImpl persistence;
    CalculatorImpl calculator;
};


int main() {
    auto provider = ServiceProviderImpl{};

    all(provider);
    two(provider);
    onlyLogger(provider);
    onlyPersist(provider);
    onlyCalculator(provider);

    return 0;
}
