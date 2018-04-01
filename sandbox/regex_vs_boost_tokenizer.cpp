#include <iostream>
#include <regex>
#include <boost/tokenizer.hpp>

int main(int argc, char** argv)
{
   std::string input = (argc > 1)? argv[1] : "0\n\n\n3\n4\n5\n6\n";

   std::cout << "regex\n";
   std::regex eol_re("\n");
   for (auto it = std::sregex_token_iterator(input.begin(), input.end(), eol_re, -1);
        it != std::sregex_token_iterator(); ++it) {
       std::cout << "<" << *it << ">\n";
   }

   std::cout << "boost::tokenizer\n";

   using tokenizer = boost::tokenizer<boost::char_separator<char>>;
   boost::char_separator<char> sep("\n", "", boost::keep_empty_tokens);
   tokenizer tok(input, sep);
   for (const auto& token : tok) {
       std::cout << "<" << token << ">\n";
   }
   std::cout << "the end\n";
   return 0;
}
