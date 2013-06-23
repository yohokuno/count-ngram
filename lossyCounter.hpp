#ifndef LOSSY_COUNTER_HPP
#define LOSSY_COUNTER_HPP

#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

template<typename Key>
class LossyCounter {
  public:
    typedef unordered_map<Key, size_t> Map;
    typedef typename Map::iterator Iterator;

    LossyCounter(const size_t capacity_) : capacity(capacity_) {
        number = 0;
        delta = 0;
    }
    void count(Key key) {
        number ++;
        if (counter.find(key) != counter.end()) {
            counter[key] ++;
        } else {
            counter[key] = delta + 1;
        }
        if (number/capacity != delta) {
            delta = number/capacity;
            for (auto i = counter.begin(); i != counter.end(); i++) {
                if (i->second < delta) {
                    counter.erase(i);
                }
            }
        }
    }
    Iterator begin() {
        return counter.begin();
    }
    Iterator end() {
        return counter.end();
    }
    size_t size() {
        return counter.size();
    }
    void takeFrequent(deque<Iterator> &result, size_t size) {
        struct Compare {
            bool operator()(Iterator a, Iterator b) {
                return a->second > b->second;
            }
        };
        priority_queue<Iterator, vector<Iterator>, Compare> que;
        for (auto i = counter.begin(); i != counter.end(); i++) {
            que.push(i);
            if (que.size() == size+1) {
                que.pop();
            }
        }
        while (!que.empty()) {
            result.push_front(que.top());
            que.pop();
        }
    }
  private:
    Map counter;
    size_t number, delta;
    const size_t capacity;
};

vector<string> parseLine(const string &line,
                         const string &beginning, const string &ending) {
    vector<string> result;
    istringstream iss(line);
    string word;

    if (beginning != "") {
        result.push_back(beginning);
    }

    while (getline(iss, word, ' ')) {
        result.push_back(word);
    }

    if (ending != "") {
        result.push_back(ending);
    }

    return result;
}
vector<string> extractNgram(const string &line, const size_t order,
                            const string &beginning, const string &ending) {
    vector<string> result;
    deque<string> context;

    for (string word : parseLine(line, beginning, ending)) {
        string ngram = word;

        for (auto i = context.rbegin(); i != context.rend(); i++) {
            result.push_back(ngram);
            ngram = *i + " " + ngram;
        }

        result.push_back(ngram);

        if (context.size() == order-1) {
            context.pop_front();
        }

        context.push_back(word);
    }

    return result;
}

#endif
