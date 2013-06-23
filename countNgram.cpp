#include <iostream>
#include "lossyCounter.hpp"

int main(const int argc, const char **argv) {
    if (argc > 1 && string(argv[1]) == "-h") {
        cerr << "Usage: count-ngram [order] [size] [beginning] [ending] [separator]\n"
            "   Count frequent n-gram from big data under limited memory.\n"
            "   Reads space-separated text from stdin and write stdout.\n"
            "   order: n-gram order [default: 3]\n"
            "   size: size of top frequent n-grams [default: 1000000]\n"
            "   beginning: sentence beginning symbol [default: ^]\n"
            "   ending: sentence ending symbol [default: ""]\n"
            "   separator: separator character [default: " "]\n";
        return 0;
    }
    const int order = (argc > 1) ? atoi(argv[1]) : 3;
    const size_t size = (argc > 2) ? atoi(argv[2]) : 1000000;
    const size_t capacity = size * 100;
    const string beginning = (argc > 3) ? argv[3] : "^";
    const string ending = (argc > 4) ? argv[4] : "";
    const string separator = (argc > 5) ? argv[5] : " ";

    LossyCounter<string> counter(capacity);

    string line;
    while (getline(cin , line)) {
        auto ngrams = extractNgram(line, order, beginning, ending);
        for (string ngram : ngrams) {
            counter.count(ngram);
        }
    }

    deque<LossyCounter<string>::Iterator> result;
    counter.takeFrequent(result, size);

    for (auto i : result) {
        cout << i->first << " " << i->second << endl;
    }

    return 0;
}
