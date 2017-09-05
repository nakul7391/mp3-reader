#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VERSION "2.1"
#define RED "\e[0;31m"
#define BLACK "\e[0;0m"
#define TEMP_MP3 "temp.mp3"
/*return the function success failure status*/
typedef enum
{
    e_failure,
    e_success
} Status;

//store values
int state[9];
char mp3_name[30];
char new_mp3_name[30];
char image_name[30];
double mp3_size;
//store file name
char *new_name[9];

FILE *fptr_mp3;
FILE *fptr_image;
FILE *fptr_temp_mp3;


typedef enum
{
  mShow,
  mTitle,
  mTrack,
  mArtist,
  mAlbum,
  mYear,
  mComment,
  mGenre,
  mAlbumArt
} Options;

#endif
