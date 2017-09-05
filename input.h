#ifndef INPUT_H
#define INPUT_H

/*print the help menu*/
void print_help_menu();

/*print the version menu*/
void print_version();

/*check input arguments*/
Status check_input_arguments( int argc, char *argv[] );

Status state_array(char *option);

#endif
