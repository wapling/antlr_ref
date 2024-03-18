parser grammar ModeTagsParser;

options { tokenVocab=ModeTagsLexer; }

file  : (tag | TEXT)* ;

tag   : '<' ID '>'
      | '<' '/' ID '>'
      ;

