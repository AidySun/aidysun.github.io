#include <iostream>
#include <set>
#include <vector>

using namespace std;

// Observer.h
class Observer {
public:
  virtual void update(string msg) = 0; // abstract virtual
};

// Subject.h

class Subject {
public:
  virtual void addObserver(Observer * observer);
  virtual void removeObserver(Observer * observer);
  virtual void notify(string msg);

private:
  std::set<Observer*> observers;
};

// Subjet.cpp

void Subject::addObserver(Observer* observer) {
  observers.insert(observer);
}

void Subject::removeObserver(Observer* observer) {
  observers.erase(observer);
}

void Subject::notify(string msg) {
  for (auto obs: observers) {
    obs->update(msg);
  }
}

// Publisher
class Publisher: public Subject {
public:
    void addArticle(const string& article) {
        articles.push_back(article);
        notify(article);
    }
private:
    vector<string> articles;
};

// Subscriber
class Subscriber: public Observer {
public:
    Subscriber(string name): name(name) {}

    virtual void update(string article) override {
        readArticle(article);
    }

    void readArticle(string article) const {
        cout << name << " is reading article : " << article << endl;
    }

private:
    string name;
};

int main() {

    Publisher publisher;

    Subscriber sub1("Tom");
    publisher.addObserver(&sub1);
    publisher.addArticle("Article 1");

    cout << endl;

    Subscriber sub2("Jerry");
    publisher.addObserver(&sub2);
    publisher.addArticle("Article 2");

    return 0;
}
