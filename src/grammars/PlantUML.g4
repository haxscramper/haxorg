grammar PlantUML;

main : TOK EOF;
TOK : 'thing';

NEWLINE : '\n' -> skip;
WORD : [A-Z_]+ ;
