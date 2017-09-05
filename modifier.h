#ifndef MODIFIER_H
#define MODIFIER_H

/*to modify the data*/
Status modify_data(int option);

/*open temp file for writing purpose*/
Status open_temp_mp3_file();

Status change_string(char begin, char end,int option);

Status copy_data();

#endif
