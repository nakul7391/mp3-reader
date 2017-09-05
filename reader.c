/*file for reader*/
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "reader.h"
#include "modifier.h"


/*read meta data function for showing command*/
Status read_meta_data()
{
    char title[50],artist[50],album[50],year[10];

    if( open_mp3_file() == e_failure )
    {
      printf("Unable to open file\n");
      return e_failure;
    }

    if( get_file_size() == e_failure )
    {
        printf("Unable to get file size\n");
        return e_failure;
    }

    if( get_data(title,'T','2') == e_failure )
    {
        printf("Unable to get title\n");
        return e_failure;
    }

    if( get_data(artist,'T','1') == e_failure )
    {
        printf("Unable to get artist\n");
        return e_failure;
    }

    if( get_data(album,'T','B') == e_failure )
    {
        printf("Unable to get album\n");
        return e_failure;
    }

    if( get_data(year,'T','R') == e_failure )
    {
        printf("Unable to get year\n");
        return e_failure;
    }


    display_file_attr(title, artist, album, year);

    if( close_mp3_file() == e_failure )
    {
        printf("Unable to close mp3 file\n");
        return e_failure;
    }
}

/*open the mp3 file in read mode*/
Status open_mp3_file()
{
    fptr_mp3 = fopen( mp3_name, "r" );

    if( fptr_mp3 == NULL )
    {
      perror("");
      return e_failure;
    }

    return e_success;
}

Status close_mp3_file()
{
    if( fclose(fptr_mp3) == 0 )
    return e_success;

    return e_failure;
}

/*get the size of mp3 file*/
Status get_file_size()
{
    fseek(fptr_mp3,0L,SEEK_END);
    mp3_size = ftell(fptr_mp3);
    rewind(fptr_mp3);

    if(ftell(fptr_mp3) == 0 )
    return e_success;

    e_failure;
}

Status get_data(char *title, char begin,char end )
{
    char byte;
    int start = 0, ext_size = 0, i_size = 0, title_size = 0;
    while( (byte = fgetc(fptr_mp3)) != EOF )
    {
        if(ext_size == 1 && i_size < 4 )
        {
          title_size = title_size << 8;
          title_size = title_size | byte;
          i_size++;
        }

        //we got the length
        if( i_size == 4)
        {
            //move the pointer 3 times forward
            fseek(fptr_mp3,3L,SEEK_CUR);
            i_size = 0;
            while( --title_size)
            {
                title[i_size] = fgetc(fptr_mp3);
                i_size++;
            }
            title[i_size] = '\0';
            break;
        }

        if( byte == begin)
        start = 1;
        if( start == 1 && byte == end )
        {
        ext_size = 1;
        start = 0;
        }
    }

    if(title[0] == '\0' )
    return e_failure;

    return e_success;
}


/*display the attributes*/
void display_file_attr(char *title, char *artist , char *album, char *year)
{
    printf("------------------------------------------------------------------\n");
    if( mp3_size > 1024 * 1024 )
    printf("%s\t%s[%.2lf MB]%s\n",mp3_name,RED,(mp3_size/(1024*1024)),BLACK);
    else if( mp3_size > 1024 )
    printf("%s\t%s[%.2lf K.B]%s\n",mp3_name,RED,(mp3_size/(1024)),BLACK);
    printf("------------------------------------------------------------------\n");
    printf("title : %s%s%s\n",RED,title,BLACK);
    printf("artist : %s%s%s\n",RED,artist,BLACK);
    printf("album : %s%s%s\n",RED,album,BLACK);
    printf("year : %s%s%s\n",RED,year,BLACK);
    printf("------------------------------------------------------------------\n");
}

Status extract_image()
{

    char image[50];
    if( open_mp3_file() == e_failure )
    {
    printf("Unable to open mp3 file\n");
    return e_failure;
    }

    if( open_jpeg_file() == e_failure )
    {
        printf("Unable to open file\n");
        return e_failure;
    }

    if( get_file_size() == e_failure )
    {
        printf("Unable to get file size\n");
        return e_failure;
    }

    if( get_write_image() == e_failure )
    {
        printf("Unable to write image\n");
        return e_failure;
    }

    printf("Image writing is successfull\n");
    printf("New image file is %s%s%s\n",RED,image_name,BLACK);

    if( close_mp3_file() == e_failure )
    {
        printf("Unable to close mp3 file\n");
        return e_failure;
    }

    if( close_image_file() == e_failure )
    {
        printf("Unable to close mp3 file\n");
        return e_failure;
    }
}

/*open jpeg file for writing*/
Status open_jpeg_file()
{
    fptr_image = fopen(image_name, "w" );

    if( fptr_image == NULL )
    {
      perror("");
      return e_failure;
    }

    return e_success;
}

Status get_write_image()
{
    unsigned char byte;

    //loop until d8 is found
    while( mp3_size > ftell(fptr_mp3) )
    {
        byte = fgetc(fptr_mp3);
        if( byte == 0xff )
        {
            byte = fgetc(fptr_mp3);
            if( byte == 0xd8 )
            {
                //fprintf(fptr_image, "%c%c",0xff,0xd8);
                fputc(0xff,fptr_image);
                fputc(0xd8,fptr_image);
                while( 1 )
                {
                    byte = fgetc(fptr_mp3);
                    fputc(byte,fptr_image);
                    if( byte == 0xff)
                    {
                        byte = fgetc(fptr_mp3);
                        if(byte == 0xd9)
                        break;
                        else
                        fseek(fptr_mp3,-1L,SEEK_CUR);
                    }
                }
                fputc(0xd9,fptr_image);
            }
        }
    }

    //check
    /*rewind(fptr_image);
    byte = fgetc(fptr_image);
    if( byte == 0xff )
    {
        printf("insdie");
        fseek(fptr_image, 0L, SEEK_END);
        fseek(fptr_image,-1L,SEEK_CUR);
        byte = fgetc(fptr_image);

        if( byte == 0xd9 )
        printf("out");
    }*/
    return e_success;
}


Status close_image_file()
{
    if( fclose(fptr_image) == 0 )
    return e_success;

    return e_failure;
}
