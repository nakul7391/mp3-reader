/*Main function for MP3 Tag reader*/
#include <stdio.h>
#include "constants.h"
#include "input.h"
#include "reader.h"
#include "modifier.h"

int main(int argc, char *argv[] )
{
		int i = 0, lock = 0;
		if( check_input_arguments( argc, argv) == e_failure )
		{
			printf("Invalid input\n");
			printf("Usage is mp3tag.out <option> <value> <file>\nmp3tag --help for help\n");
			return 1;
		}

		/*check state array*/
		if( state[mShow] == 1 )
		{
				if( read_meta_data() == e_failure )
				{
					printf("Unable to read meta data\n");
					return 1;
				}
		}
		else if(state[mAlbumArt] == 1)
		{
				//extract image
				if( extract_image() == e_failure )
				{
						printf("Unable to extract image\n");
						return 1;
				}
		}

	/*for(i = 0; i< 8; i++)
		printf("%s ",new_name[i]);
		printf("\n");
				for(i = 0; i< 8; i++)
			printf("%d ",state[i]);
			printf("\n");*/
		for( i = 1; i < 8; i++ )
		{
				if( state[i] == 1 )
				{
						lock = 1;
						modify_data(i);
				}
		}

		if( lock == 1 )
		{
		printf("Mofication successfull\nNew file is %s%s%s\n",RED,new_mp3_name,BLACK);
		remove(TEMP_MP3);
		}
	//	for( i = 0 ;i < 9; i++ )
		//printf("%d \n",state[i]);

		return 0;
}
