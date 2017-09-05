#ifndef READER_H
#define READER_H
/*to read meta data*/
Status read_meta_data();

/*open file*/
Status open_mp3_file();

/*get size of the file*/
Status get_file_size();

/*get title of the file*/
Status get_data(char *title, char begin, char end);

void display_file_attr(char *title, char *artist,char *album, char *year);

Status close_mp3_file();

/*extract the image*/
Status extract_image();

/*create new file jpeg*/
Status open_jpeg_file();

/*get and write image data*/
Status get_write_image();

/*close image file*/
Status close_image_file();
#endif
