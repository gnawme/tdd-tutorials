/*! Implements Soundex encoding ---------------------------------------------*\
| \see https://en.wikipedia.org/wiki/Soundex
\*---------------------------------------------------------------------------*/
#ifndef SOUNDEX_SOUNDEX_H
#define SOUNDEX_SOUNDEX_H

#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

class Soundex {
    const int cMaxEncodedLength{4};
public:

    //!
    std::string encode(const std::string& word)
    {
        std::string disemvoweled = disemvowel(word);
        std::stringstream ss;
        ss << disemvoweled[0];
        for (auto i = 1; i < disemvoweled.length(); ++i) {
            std::string encoded = encodedDigit(disemvoweled[i]);
            if (!encoded.empty()) {
                ss << encoded;
            }

            if (isComplete(ss.str())) {
                break;
            }
        }

        std::string encoded = (ss.str().length() < cMaxEncodedLength ? zeroPad(ss.str()) : ss.str());
        return encoded;
    }

private:

    //!
    std::string disemvowel(const std::string& word)
    {
        const std::map<char, char> discards = {
            {'a', 'a'}, {'e', 'e'}, {'i', 'i'}, {'o', 'o'}, {'u', 'u'}, {'y', 'y'}, {'h', 'h'}, {'w', 'w'}
        };

        std::stringstream ss;
        ss << word[0];
        for (auto i = 1; i < word.length(); ++i) {
            if (discards.find(word[i]) == discards.end()) {
                ss << word[i];
            }
        }

        return std::string(ss.str());
    }

    //!
    std::string encodedDigit(char digit)
    {
        const std::unordered_map<char, std::string> encodings = {
            {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
            {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
            {'d', "3"}, {'t', "3"},
            {'l', "4"},
            {'m', "5"}, {'n', "5"},
            {'r', "6"}
        };

        if (encodings.find(digit) != encodings.end()) {
            return std::string(encodings.find(digit)->second);
        }

        return std::string();
    }
    
    //!
    bool isComplete(const std::string& encoded)
    {
        return encoded.length() == cMaxEncodedLength;
    }

    //!
    std::string zeroPad(const std::string& word)
    {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(4) << std::left << word;
        return std::string(ss.str());
    }
};

#endif //SOUNDEX_SOUNDEX_H
