count-ngram
===========

Count frequent n-gram from big data with limited memory.

It processes 100GB text data within 23 hours on 8GB machine, yielding 1 million top frequent word n-grams. This implements Lossy Counting Algorithm [Manku and Motwani, 2002].

> G. Manku and R. Motwani. Approximate frequency counts over data streams. In International Conference on Very Large Data Bases, pages 346-357, 2002

For people who are not familiar with natural language processing, an n-gram is a sequence of adjacent n words in corpus. Counting n-grams is an essential for language models, which perform important role in machine translation, speech recognition, optical character recognition, spelling correction and text input method.

Install
-----------

    ./waf configure
    ./waf build
    ./waf build/test
    sudo ./waf install

Usage
-----------
    count-ngram [order] [size] [beginning] [ending] [separator]
        Count frequent n-gram from big data under limited memory.
        Reads space-separated text from stdin and write stdout.
        order: n-gram order [default: 3]
        size: size of top frequent n-grams [default: 1000000]
        beginning: sentence beginning symbol [default: ^]
        ending: sentence ending symbol [default: ""]
        separator: separator character [default: " "]

Example
-----------
    cat input.txt | count-ngram 3 10
        the 88
        she 73
        to 71
        and 56
        ^ 55
        a 52
        was 52
        of 41
        it 41
        her 24
