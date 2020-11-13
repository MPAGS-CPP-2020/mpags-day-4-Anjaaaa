#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <string>
#include <vector>
#include <map>

// Our project headers
#include "CipherMode.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the playfair cipher with the given key
 * 
 * This class can encrypt any input text using the playfair cipher. The input
 * text should only contain symbols belonging to the standard English alphabet.
 * Any other symbols including empty spaces will be removed.
 * The deciphering process only reverts the shifts in the key-grid. It does not
 * remove the X and Q characters inserted between double symbols as this could
 * alter the meaning of statements (i.e. "complex example" requires an x between
 * two e).
 */
class PlayfairCipher {
  public:
    /**
     * Create a new PlayfairCipher, converting the given string into the key
     *
     * \param key the string to convert into the key to be used in the cipher
     */
    explicit PlayfairCipher( const std::string& key );

    /**
     * Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;

  private:
    /// The alphabet - used to determine the cipher character given the plain character and the key
    const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    /// The size of the alphabet
    const std::vector<char>::size_type alphabetSize_ = alphabet_.size();

    /// The cipher key, essentially a constant shift to be applied
    std::string key_ = "";

    /// The setKey function
    void setKey(const std::string& key);

    using Str2CoordMap = std::map<char,std::pair<int,int>>;
    /// A map encoding the position of a character
    Str2CoordMap location_;

    using Coord2StrMap = std::map<std::pair<int,int>,char>;
    /// A map encoding the content of a position
    Coord2StrMap content_;
};

#endif
