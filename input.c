/*This file will take the input arguments */
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "input.h"

Status check_input_arguments( int argc, char *argv[] )
{
		char *extn = NULL;
		int optionlen, argcount, i = 2, j = 1;
    //if no arguments only output file
    if(argc == 1 )
		{
    return e_failure;
		}

    //if two arguments it must be help or file name or version name
    if( argc == 2 )
    {
        if( strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-h") == 0 )
        {
						print_help_menu();
						return e_success;
				}
				else if( strcmp(argv[1],"-v") == 0 )
				{
						print_version();
						return e_success;
				}
				//check if argument contains .mp3 then store that file name
				else if( (extn = strstr(argv[1],".mp3")) != NULL )
				{
						//store file name
						strcpy(mp3_name,argv[1]);
						state[mShow] = 1;
						return e_success;
				}
    }
		//if the option is -i
		else if( strcmp(argv[1],"-i") == 0 && argv[3] != NULL && (extn = strstr(argv[3],".mp3") ) != NULL )
		{
					strcpy(mp3_name,argv[3]);
					strcpy(image_name,argv[2]);
					state[mAlbumArt] = 1;
					return e_success;
		}
		//arguments are greate then 2 check number of options after -
		else
		{
			//if argument 1 contain option other than predefined
			optionlen =	strlen(argv[1]);
			optionlen = optionlen - 1; //remove -
			argcount = argc - 4; //ignore file name option and output
			if( optionlen != argcount)
			return e_failure;

			/*fill the array and check if any other variables are there in the argument*/
			if( state_array(argv[1]) == e_failure )
			return e_failure;

			//fill name array
			for( j = 1, i = 2; j < 8; j++ )
			{
				if(state[j] == 1)
				new_name[j] = argv[i++];
			}

			strcpy(mp3_name, argv[i++]);
			if( argv[i] != NULL )
			strcpy(new_mp3_name, argv[i]);
			else
			return e_failure;

			return e_success;

		}
}

void print_help_menu()
{
		printf("----------------------------------------------------------------------\n");
		printf("%sUsage:%s ./mp3tag.o %s(in sequence)%s -[tTaAycg] \"value\" <source mp3> <new mp3>\n",RED,BLACK,RED,BLACK);
		printf("         mp3tag <source mp3>\n");
		printf("         mp3tag -v\n");
		printf("         mp3tag -i < image name > <mp3>\n");
		printf("         mp3tag -h\n");
		printf("-t    Modifies a Title tag\n");
		printf("-T    Modifies a Track tag\n");
		printf("-a    Modifies a Artist tag\n");
		printf("-A    Modifies a Album tag\n");
		printf("-y    Modifies a Year tag\n");
		printf("-c    Modifies a Comment tag\n");
		printf("-g    Modifies a Genre tag\n");
		printf("-i    Extracts Album art\n");
		printf("-h    Displays help info\n");
		printf("-v    Prints version info\n");
		printf("----------------------------------------------------------------------\n");
}

void print_version()
{
		printf("mp3tag version %s\n",VERSION);
}

/*fill the array*/
Status state_array(char *option)
{
	int i = 1;
	//fill the array
	while ( option[i] != '\0' )
	{
			switch(option[i])
			{
					case 't':state[mTitle] = 1;
									break;
					case 'T':state[mTrack] = 1;
									break;
					case 'a':state[mArtist] = 1;
									break;
					case 'A':state[mAlbum] = 1;
									break;
					case 'y':state[mYear] = 1;
									break;
					case 'c':state[mComment] = 1;
									break;
					case 'g':state[mGenre] = 1;
									break;
					default:return e_failure;
									break;
			}
			i++;
	}
	return e_success;
}
