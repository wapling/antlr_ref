grammar CSV;

@header {
#ifndef CSV_HEADER_
#define CSV_HEADER_

#include <cctype>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

typedef std::unordered_map<std::string, std::string> ValuesMap;
typedef std::vector<std::string> RowVector;

namespace {

  inline std::string trim(std::string s)
  {
    if (s.empty())
      return s;

    while (!s.empty() && std::isspace(*s.begin()))
      s = s.substr(1);

    while (!s.empty() && std::isspace(*s.rbegin()))
      s = s.substr(0, s.length() - 1);

    return s;
  }

  inline RowVector split(std::string const& s, char delim)
  {
    RowVector vec;
    std::size_t start = 0, end = 0;
    while ((end = s.find(delim, start)) != std::string::npos)
    {
      vec.push_back(s.substr(start, end - start));
      start = end + 1;
    }
    vec.push_back(s.substr(start));
    return vec;
  }

  template <typename K, typename V>
  std::ostream& operator<<(std::ostream& ostrm, std::unordered_map<K, V> const& data)
  {
    ostrm << '{';
    bool first_time = true;
    for (auto const& datum : data)
    {
      if (first_time)
        first_time = false;
      else
        ostrm << ", ";
      ostrm << datum.first << ": " << datum.second;
    }
    ostrm << '}';
    return ostrm;
  }
}//anonymous namespace
#endif
}

file
locals [int i=0]
  : hdr ( rows+=row[split($hdr.text, ',')] {$i++;} )+
    {
      std::cout << $i << " rows" << std::endl;
      for (RowContext* r : $rows)
      {
        std::cout << "row token interval: " << r->getSourceInterval().toString() << std::endl;
      }
    }
  ;
 
hdr : row[RowVector()] {std::cout << "header: '" << trim($text) << "'" << std::endl;} ;

row[RowVector columns] returns [ValuesMap values]
locals [int col=0]
@init {
}
@after {
  if ($values.size() > 0)
    std::cout << "values = " << $values << std::endl;
}
    : field 
      {
        if (!$columns.empty())
          $values.insert_or_assign(trim($columns[$col++]), trim($field.text));
      }    
      ( ',' field
        {
          if (!$columns.empty())
            $values.insert_or_assign(trim($columns[$col++]), trim($field.text));
        }
      )* NL
    ;

field : TEXT          #text
      | STRING        #string
      |               #empty
      ;


NL      : '\r'? '\n' ;
TEXT    : ~[,\n\r"]+ ;
STRING  : '"' ('""'|~'"')* '"' ;
