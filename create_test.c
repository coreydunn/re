/*
 * Make random slideshow
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

int main(int argc,char**argv)
{
	int fd;
	size_t no_para;
	char*con="bcdfghjklmnpqrstvwxyz";
	char*vow="aeiou";
	size_t max_word_len=10;
	size_t max_para=400;
	size_t max_words=100;
	size_t chance_space=5;

	srand(time(NULL));

	if(argc<2)
	{
		fprintf(stderr,"usage: %s FILENAME\n",*argv);
		return 1;
	}

	if((fd=open(argv[1],O_CREAT|O_WRONLY,0660))<0)
	{
		fprintf(stderr,"error: failed to open '%s'\n",argv[1]);
		return 1;
	}

	no_para=rand()%max_para+1;
	for(size_t i=0;i<no_para;++i)
	{
		size_t no_words=rand()%max_words+1;

		for(size_t j=0;j<no_words;++j)
		{
			size_t word_len=rand()%max_word_len+1;
			char word[128];
			static char last_space=0;

			for(size_t k=0;k<word_len;++k)
			{
				if(k%2)
					word[k]=con[rand()%strlen(con)];
				else
					word[k]=vow[rand()%strlen(vow)];
			}

			write(fd,word,word_len);
			if(j<no_words-1)
			{
				if(last_space=='\n')
				{
					last_space=' ';
					write(fd," ",1);
				}

				else
				{
					last_space=(rand()%chance_space)==0?'\n':' ';
					write(fd,last_space==' '?" ":"\n",1);
				}
			}
		}
		if(i<no_para-1)
			write(fd,"\n\n",2);
	}
	close(fd);
}
