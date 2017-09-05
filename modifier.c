/*to modify the mp3 header*/
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "reader.h"
#include "modifier.h"

Status modify_data(int option)
{
    unsigned char byte;
    int i = 0;

    if( open_mp3_file() == e_failure )
    {
    printf("Unable to open file\n");
    return e_failure;
    }

    if( open_temp_mp3_file() == e_failure )
    {
    printf("Unable to open file\n");
    return e_failure;
    }

    if( get_file_size() == e_failure )
    {
        printf("Unable to get file size\n");
        return e_failure;
    }

    switch(option)
    {
      case 1:change_string('T','2',option); //for title
              break;
      case 3:change_string('T','1',option); //for artist
              break;
      case 4:change_string('T','B',option); //for album
              break;
      case 5:change_string('T','R',option); //for year
              break;
      default:printf("No data avilable\n");
              break;
    }

    if( close_mp3_file() == e_failure )
    {
        printf("Unable to close mp3 file\n");
        return e_failure;
    }

    strcpy(mp3_name,new_mp3_name);

  //
    /*close temp the delete it*/
    if(fclose(fptr_temp_mp3) != 0 )
    return e_failure;

    /*copy all data to user given file*/
    copy_data();
    //remove(TEMP_MP3);
}

/*open the temp mp3 file in write mode*/
Status open_temp_mp3_file()
{
    fptr_temp_mp3 = fopen( TEMP_MP3, "w" );

    if( fptr_temp_mp3 == NULL )
    {
      perror("");
      return e_failure;
    }

    return e_success;
}

Status change_string(char begin , char end, int option)
{
    char byte;
    int start = 0, ext_size = 0, i_size = 0, title_size = 0, i = 0, count = 0, lock = 0;

    while( (byte = fgetc(fptr_mp3)) != EOF )
    {
        //get the size
        if(ext_size == 1 && i_size < 4 )
        {
          title_size = title_size << 8;
          title_size = title_size | byte;
          i_size++;
          if( i_size == 4)
          fputc(byte,fptr_temp_mp3);
        }

        //we got the length
        if( i_size == 4)
        {
            //put three flag bytes
            for( i = 0; i < 3; i++ )
            {
                byte = fgetc(fptr_mp3);
                fputc(byte,fptr_temp_mp3);
            }

            i_size = 0; i = 0;
            while(--title_size)
            {
                if(new_name[option][i] != '\0' )
                {
                byte = fgetc(fptr_mp3);
                fputc(new_name[option][i],fptr_temp_mp3);
                i++;
                }
                else
                {
                byte = fgetc(fptr_mp3);
                fputc(0x0,fptr_temp_mp3);
                }
                i_size++;
            }
            break;
        }

        if( byte == begin)
        {
        start = 1;
        }
        if( start == 1 && byte == end )
        {
              ext_size = 1;
              start = 0;
        }
        //insert data
        fputc(byte,fptr_temp_mp3);
    }
    //after break control comes here
    while(mp3_size > ftell(fptr_mp3))
    {
        byte = fgetc(fptr_mp3);
        fputc(byte,fptr_temp_mp3);
    }

    return e_success;
}

Status copy_data()
{
    unsigned char byte;
    /*open user file*/
    FILE *fptr_new_mp3 = fopen(new_mp3_name,"w");
    /*open temp file in read mode*/
    fptr_temp_mp3 = fopen(TEMP_MP3,"r");

    while(mp3_size > ftell(fptr_temp_mp3))
    {
        byte = fgetc(fptr_temp_mp3);
        fputc(byte,fptr_new_mp3);
    }


    fclose(fptr_temp_mp3);
    fclose(fptr_new_mp3);
}
