#include <iostream>
extern int yylex(void);
extern int yyparse();
extern int yyerror(char*);
extern char final_string[10001];
extern void connect(char[],char[]);
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_buffer(char *,size_t);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
