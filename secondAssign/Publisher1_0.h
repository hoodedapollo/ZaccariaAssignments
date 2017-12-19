#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

using namespace std;


class Publisher {
        private:
                int publishing_period;
                int pipe_filedes_reading;
                int pipe_filedes_writing;

        public:
                Publisher(int);
                void set_period(int); // set publishing period
                void set_pipe_filedes(int, int); // set file descriptor attributes
                void set_pipe_filedes(char*,char*); // if file des are chars convert them into int before setting the corresponding attributes
                void write_in_pipe(); // generate a random char and write it in the pipe at a given frequency
};

Publisher::Publisher (int pub_period)
{
        publishing_period = pub_period;
}

void Publisher::set_period(int pub_period)
{
        publishing_period = pub_period; // seconds
}

void Publisher::set_pipe_filedes( int filedes0, int filedes1)
{
        pipe_filedes_reading = filedes0;
        pipe_filedes_writing = filedes1;
        close(pipe_filedes_reading);
}

void Publisher::set_pipe_filedes( char *filedes0, char *filedes1)
{
        pipe_filedes_reading = atoi(filedes0);
        pipe_filedes_writing = atoi(filedes1);
        close(pipe_filedes_reading);
}



void Publisher::write_in_pipe ()
{
        sleep(publishing_period);
        char randomletter = 'A' + (random() % 26);
        int write_return = write(pipe_filedes_writing, &randomletter, sizeof(char));
}
    
