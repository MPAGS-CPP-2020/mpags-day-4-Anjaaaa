
// Standard library includes
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

// Out project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher(const std::string& key)
  : key_{key}
{
    setKey(key);
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode ) const
{
    std::cout << inputText << std::endl;
    // Initialize output string
    std::string outputText{inputText};
    int alter{0};
    // Make sure the string is upper case
    std::transform(outputText.begin(), outputText.end(), outputText.begin(), ::toupper);
    if (cipherMode==CipherMode::Encrypt)
    {
        // Remove non-alpha characters
        auto iter = std::remove_if(outputText.begin(), outputText.end(),
            [](char c){return !std::isalpha(c);});
        outputText.erase(iter,outputText.end());
        // Change J -> I
        std::transform(outputText.begin(), outputText.end(), outputText.begin(),
            [] (char c){return (c=='J') ? 'I': c;}
        );
        // If repeated chars in a digraph add an X or Q if XX
        for (size_t i = 1; i < outputText.length(); i++)
        {
            if (outputText[i]==outputText[i-1]){
                if (outputText[i]=='X') outputText.insert(i,"Q");
                else outputText.insert(i,"X");
            }
        }
        // If the size of input is odd, add a trailing Z
        if (outputText.length()%2==1) outputText += "Z";
        alter++;
    } else alter--;
    // Loop over the input in digraphs
    int index{0};
    for (auto it{outputText.begin()}; it != outputText.end(); it+=2)
    {
        // Find the coords in the grid
        auto loc1 = (*location_.find(*it)).second;
        auto loc2 = (*location_.find(*(it+1))).second;
        std::pair<int,int> newLoc1{0,0};
        std::pair<int,int> newLoc2{0,0};
        // Apply the rules 1) same row -> take letter to the right
        if (loc1.first==loc2.first)
        {
            newLoc1 = {loc1.first,(loc1.second+alter)%5};
            newLoc2 = {loc2.first,(loc2.second+alter)%5};
        }
        // Apply the rules 2) same column -> take letter below
        else if (loc1.second==loc2.second)
        {
            newLoc1 = {(loc1.first+alter)%5,loc1.second};
            newLoc2 = {(loc2.first+alter)%5,loc2.second};
        }
        // Apply the rules 3) rectangle
        else
        {
            newLoc1 = {loc1.first,loc2.second};
            newLoc2 = {loc2.first,loc1.second};
        }
        // Find the letter associated with the new coords
        outputText[index] = (*content_.find(newLoc1)).second;
        outputText[index+1] = (*content_.find(newLoc2)).second;
        index += 2;
    }
    // return the text
    return outputText;
}

void PlayfairCipher::setKey(const std::string& key)
{
    key_ = key;
    // Append the alphabet
    for(auto iter{std::begin(alphabet_)}; iter != alphabet_.end(); iter++){
        key_.push_back(*iter);
    }
    // Make sure the key is upper case
    std::transform(key_.begin(), key_.end(), key_.begin(), ::toupper);
    // Remove non-alpha characters
    auto iter = std::remove_if(key_.begin(), key_.end(),
        [](char c){return !std::isalpha(c);});
    key_.erase(iter,key_.end());
    // Change J -> I
    std::transform(key_.begin(), key_.end(), key_.begin(),
        [] (char c){return (c=='J') ? 'I': c;}
    );
    // Remove duplicated letters
    std::string alreadyIn{""};
    auto iter2 = std::remove_if(key_.begin(), key_.end(),
        [&](char c){
            // Check if the character is already in the key
            if (alreadyIn.find(c)<alreadyIn.length()) {
                return true;}
            else {alreadyIn += c; return false;}
            });
    key_.erase(iter2,key_.end());
    // Store the coords of each letter
    int index{0};
    for (auto it{key_.begin()}; it!=key_.end();it++){
        int col = index%5;
        int row = (index-col)/5;
        std::pair<int,int> pos{ row, col };
        location_[*it] = pos;
        content_[pos] = *it;
        index++;
    }
    std::cout << key_ << std::endl;
    // Store the playfair cipher key map
    /*
        Done by implementing two new private variables.
    */
}