#include <iostream>
#include <set>
#include <vector>
#include <memory>

using namespace std;

enum EventType {
    ARTICLE_UPDATED,
    VIP_ARTICLE_UPDATED
};

class Event {
public:
    virtual EventType type() const = 0;
    virtual ~Event() {}
};

// 具体的 Event 类型
class ArticleUpdatedEvent: public Event {
public:
    virtual EventType type() const override { return ARTICLE_UPDATED; }

    string getArticle() const { return article; }
    void setArticle(const string& article) { this->article = article; }
private:
    string article;
};

class VipArticleUpdatedEvent: public Event {
public:
    virtual EventType type() const override { return VIP_ARTICLE_UPDATED; }

    string getArticle() const { return article; }
    void setArticle(const string& article) { this->article = article; }

    int getReward() const { return reward; }
    void setReward(int reward) { this->reward = reward; }
private:
    string article;
    int reward;
};

// Observer.h
class Observer {
public:
  virtual void update(shared_ptr<Event> event) = 0; // abstract virtual
};

// Subject.h

class Subject {
public:
  virtual void addObserver(Observer * observer);
  virtual void removeObserver(Observer * observer);
  virtual void notify(shared_ptr<Event> event);

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

void Subject::notify(shared_ptr<Event> event) {
  for (auto obs: observers) {
    obs->update(event);
  }
}


// Publisher
class Publisher: public Subject {
public:
    void addArticle(const string& article) {
        auto e = make_shared<ArticleUpdatedEvent>();
        e->setArticle(article);
        notify(e);
    }
    
    void addVipArticleWithReward(const string& article, int reward) {
        auto e = make_shared<VipArticleUpdatedEvent>();
        e->setArticle(article);
        e->setReward(reward);
        notify(e);
    }
};

// Subscriber
class Subscriber: public Observer {
public:
    Subscriber(string name): name(name) {}

   virtual void update(shared_ptr<Event> event) override {
        switch (event->type()) {
            case EventType::ARTICLE_UPDATED: {
                auto e = dynamic_cast<ArticleUpdatedEvent*>(event.get());
                if (e != nullptr) {
                    string article = e->getArticle();
                    readArticle(article);
                }
                break;
            }
            case EventType::VIP_ARTICLE_UPDATED: {
                auto e = dynamic_cast<VipArticleUpdatedEvent*>(event.get());
                if (e != nullptr) {
                    string vipArticle = e->getArticle();
                    readArticle(vipArticle);
                    int reward = e->getReward();
                    earnReward(reward);
                }
                break;
            }
            default:
                break;
        }
    }

    void readArticle(string article) const {
        cout << name << " is reading article : " << article << endl;
    }

    void earnReward(int reward) const {
        cout << name << " earned reward : " << reward << endl;
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
    publisher.addVipArticleWithReward("Article 2", 5);

    return 0;
}
